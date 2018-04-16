//
//  VMM.c
//  VMM
//
//  Created by Greyson Wright on 4/15/18.
//  Copyright © 2018 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define TLB_SIZE 16
#define PAGES 256
#define PAGE_MASK 255
#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255
#define MEM_SIZE PAGES * PAGE_SIZE
#define BUFFER_SIZE 10

typedef struct TLBRow {
    unsigned char logical;
    unsigned char physical;
} TLBRow;

void initBackingStore(void);
void initPageTable(void);
int searchTLB(unsigned char);
int max(int, int);
void addTLB(unsigned char, unsigned char);
void printStats(int, int, int);

TLBRow tlb[TLB_SIZE];
int tlbIndex = 0;
int pageTable[PAGES];
signed char mainMem[MEM_SIZE];
signed char *backingStore;

int main(int argc, const char **argv) {
	int addressCount = 0;
	int tlbHits = 0;
	int pageFaultCount = 0;
	char buffer[BUFFER_SIZE];
	
	if (argc != 2) {
        fprintf(stderr, "Please provide the correct arguments.\n");
		return -1;
    }
	
    FILE *input_fp = fopen(argv[1], "r");
	initBackingStore();
	initPageTable();
    
    while (fgets(buffer, BUFFER_SIZE, input_fp) != NULL) {
        int logicalAddress = atoi(buffer);
        int offset = logicalAddress & OFFSET_MASK;
        int logicalPage = (logicalAddress >> OFFSET_BITS) & PAGE_MASK;
        int physicalPage = searchTLB(logicalPage);
		
        if (physicalPage != -1) {
            tlbHits++;
        } else {
            physicalPage = pageTable[logicalPage];
            if (physicalPage == -1) {
                physicalPage = pageFaultCount;
				pageFaultCount++;
                memcpy(mainMem + physicalPage * PAGE_SIZE, backingStore + logicalPage * PAGE_SIZE, PAGE_SIZE);
                pageTable[logicalPage] = physicalPage;
            }
            addTLB(logicalPage, physicalPage);
        }
        
        int physicalAddress = (physicalPage << OFFSET_BITS) | offset;
        signed char value = mainMem[physicalPage * PAGE_SIZE + offset];
        printf("Virtual address: %d Physical address: %d Value: %d\n", logicalAddress, physicalAddress, value);
		addressCount++;
    }
	
	printStats(addressCount, pageFaultCount, tlbHits);
    return 0;
}

void initBackingStore(void) {
	int backingFile = open("BACKING_STORE.bin", O_RDONLY);
	backingStore = mmap(0, MEM_SIZE, PROT_READ, MAP_PRIVATE, backingFile, 0);
}

void initPageTable(void) {
	int i;
	for (i = 0; i < PAGES; i++) {
		pageTable[i] = -1;
	}
}

int searchTLB(unsigned char logical_page) {
	int i;
	for (i = max((tlbIndex - TLB_SIZE), 0); i < tlbIndex; i++) {
		TLBRow *row = &tlb[i % TLB_SIZE];	
		if (row->logical == logical_page) {
			return row->physical;
		}
	}
	return -1;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void addTLB(unsigned char logical, unsigned char physical) {
	TLBRow *row = &tlb[tlbIndex % TLB_SIZE];
	row->logical = logical;
	row->physical = physical;
	tlbIndex++;
}

void printStats(int addressCount, int pageFaultCount, int tlbHits) {
	double pageFaultRate = pageFaultCount / (1. * addressCount);
	double tlbHitRate = tlbHits / (1. * addressCount);
	printf("Number of Translated Addresses = %d\nPage Faults = %d\nPage Fault Rate = %.3f\nTLB Hits = %d\nTLB Hit Rate = %.3f\n", addressCount, pageFaultCount, pageFaultRate, tlbHits, tlbHitRate);
}
