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
#define FRAME_COUNT 256
#define FRAME_SIZE 256
#define OFFSET_BITS 8
#define MEM_SIZE FRAME_COUNT * FRAME_SIZE

typedef struct TLBRow {
    unsigned char logical;
    unsigned char physical;
} TLBRow;

typedef struct TLB {
	TLBRow store[TLB_SIZE];
	int index;
} TLB;

TLB *newTLB(void);
char *initBackingStore(void);
void initPageTable(void);
void insertPageTable(int, int, char *);
int findTLB(unsigned char, TLB *);
int max(int, int);
void insertTLB(unsigned char, unsigned char, TLB *);
void printStats(int, int, int);

int pageTable[FRAME_COUNT];
char memory[MEM_SIZE];

int main(int argc, const char **argv) {
	int addressCount = 0;
	int tlbHits = 0;
	int pageFaultCount = 0;
	TLB *tlb = newTLB();
	
	if (argc != 2) {
        fprintf(stderr, "Please provide the correct arguments.\n");
		return -1;
    }
	
    FILE *input_fp = fopen(argv[1], "r");
	char *backingStore = initBackingStore();
	initPageTable();
	
	char addressString[10];
    while (fgets(addressString, 10, input_fp) != NULL) {
        int logicalAddress = atoi(addressString);
        int offset = logicalAddress & 255;
        int logicalPage = (logicalAddress >> OFFSET_BITS) & 255;
        int physicalPage = findTLB(logicalPage, tlb);
		
        if (physicalPage != -1) {
            tlbHits++;
        } else {
            physicalPage = pageTable[logicalPage];
            if (physicalPage == -1) {
				physicalPage = pageFaultCount++;
				insertPageTable(physicalPage, logicalPage, backingStore);
            }
            insertTLB(logicalPage, physicalPage, tlb);
        }
        
        int physicalAddress = (physicalPage << OFFSET_BITS) | offset;
        char value = memory[physicalPage * FRAME_SIZE + offset];
        printf("Virtual address: %d Physical address: %d Value: %d\n", logicalAddress, physicalAddress, value);
		addressCount++;
    }
	
	printStats(addressCount, pageFaultCount, tlbHits);
    return 0;
}

TLB *newTLB(void) {
	TLB *tlb = malloc(sizeof *tlb);
	tlb->index = 0;
	return tlb;
}

char *initBackingStore(void) {
	int backingFile = open("BACKING_STORE.bin", O_RDONLY);
	char *backingStore = mmap(0, MEM_SIZE, PROT_READ, MAP_PRIVATE, backingFile, 0);
	return backingStore;
}

void initPageTable(void) {
	int i;
	for (i = 0; i < FRAME_COUNT; i++) {
		pageTable[i] = -1;
	}
}

void insertPageTable(int physicalPage, int logicalPage, char *backingStore) {
	memcpy(memory + physicalPage * FRAME_SIZE, backingStore + logicalPage * FRAME_SIZE, FRAME_SIZE);
	pageTable[logicalPage] = physicalPage;
}

int findTLB(unsigned char logical_page, TLB *tlb) {
	int i;
	for (i = max((tlb->index - TLB_SIZE), 0); i < tlb->index; i++) {
		TLBRow *row = &tlb->store[i % TLB_SIZE];
		if (row->logical == logical_page) {
			return row->physical;
		}
	}
	return -1;
}

int max(int a, int b) {
	return a > b ? a : b;
}

void insertTLB(unsigned char logical, unsigned char physical, TLB *tlb) {
	TLBRow *row = &tlb->store[tlb->index++ % TLB_SIZE];
	row->logical = logical;
	row->physical = physical;
}

void printStats(int addressCount, int pageFaultCount, int tlbHits) {
	double pageFaultRate = pageFaultCount / (1. * addressCount);
	double tlbHitRate = tlbHits / (1. * addressCount);
	printf("Number of Translated Addresses = %d\nPage Faults = %d\nPage Fault Rate = %.3f\nTLB Hits = %d\nTLB Hit Rate = %.3f\n", addressCount, pageFaultCount, pageFaultRate, tlbHits, tlbHitRate);
}
