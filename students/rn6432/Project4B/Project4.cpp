/*
 * Project4.cpp
 */

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include "Invent.h"

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
uint32_t num_customers = 0;

// item types
String bottles;
String rattles;
String diapers;
String custom1;
String custom2;

bool custom1_taken = false;
bool custom2_taken = false;

// main inventory
int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;
int num_custom1 = 0;
int num_custom2 = 0;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
	for (int i = 0; i < num_customers; i++) {
		StringDestroy(&(customers[i].name));
	}
	if (custom1_taken == true) {
		StringDestroy(&custom1);
	}
	if (custom2_taken == true) {
		StringDestroy(&custom2);
	}
	num_bottles = 0;
	num_rattles = 0;
	num_diapers = 0;
	num_custom1 = 0;
	num_custom2 = 0;
	num_customers = 0;	
}

void processSummarize(void) {
	int max_diapers = 0;
	int max_bottles = 0;
	int max_rattles = 0;
	int max_custom1 = 0;
	int max_custom2 = 0;
	String max_diaper_name;
	String max_bottle_name;
	String max_rattle_name;
	String max_custom1_name;
	String max_custom2_name;

	if (custom1_taken == false) {
		printf("There are %d diapers, %d bottles and %d rattles in inventory\n", num_diapers, num_bottles, num_rattles);
	} else if (custom1_taken == true && custom2_taken == false) {
		printf("There are %d diapers, %d bottles, %d rattles, and %d ", num_diapers, num_bottles, num_rattles, num_custom1);
		StringPrint(&custom1);
		printf(" in inventory\n");	
	} else {
		printf("There are %d diapers, %d bottles, %d rattles, %d ", num_diapers, num_bottles, num_rattles, num_custom1);
		StringPrint(&custom1);
		printf(", and %d ", num_custom2);
		StringPrint(&custom2);
		printf(" in inventory\n");
	}
	printf("we have had a total of %d different customers\n", num_customers);

	// find most diapers, bottles, and rattles
	for (int i = 0; i < num_customers; i++) {
		Customer c = (Customer) customers[i];
		if (c.diapers > max_diapers) {
			max_diapers = c.diapers;
			max_diaper_name = c.name;
		} 
		if (c.bottles > max_bottles) {
			max_bottles = c.bottles;
			max_bottle_name = c.name;
		} 
		if (c.rattles > max_rattles) {
			max_rattles = c.rattles;
			max_rattle_name = c.name;
		}
		if (c.custom1 > max_custom1) {
			max_custom1 = c.custom1;
			max_custom1_name = c.name;
		}
		if (c.custom2 > max_custom2) {
			max_custom2 = c.custom2;
			max_custom2_name = c.name;
		}
	}
	if (max_diapers == 0) {
		printf("no one has purchased any diapers\n");
	} else {
		StringPrint(&max_diaper_name);
		printf(" has purchased the most diapers (%d)\n", max_diapers);
	}
	if (max_bottles == 0) {
		printf("no one has purchased any bottles\n");
	} else {
		StringPrint(&max_bottle_name);
		printf(" has purchased the most bottles (%d)\n", max_bottles);
	}
	if (max_rattles == 0) {
		printf("no one has purchased any rattles\n");
	} else {
		StringPrint(&max_rattle_name);
		printf(" has purchased the most rattles (%d)\n", max_rattles);
	}
	if (custom1_taken == true) {
		if (max_custom1 == 0) {
			printf("no one has purchased any ");
			StringPrint(&custom1);
			printf("\n");
		} else {
			StringPrint(&max_custom1_name);
			printf(" has purchased the most ");
			StringPrint(&custom1);
			printf(" (%d)\n", max_custom1);
		}
	}
	if (custom2_taken == true) {
		if (max_custom2 == 0) {
			printf("no one has purchased any ");
			StringPrint(&custom2);
			printf("\n");
		} else {
			StringPrint(&max_custom2_name);
			printf(" has purchased the most ");
			StringPrint(&custom2);
			printf(" (%d)\n", max_custom2);
		}		
	}
}

void processPurchase(void) {
	bottles = StringCreate("Bottles");
	rattles = StringCreate("Rattles");
	diapers = StringCreate("Diapers");

	String item_type;
	String customer;
	int quantity;

	// read args
	readString(&customer);
	readString(&item_type);
	readNum(&quantity);

	// check if there is enough inventory available
	if ((StringIsEqualTo(&bottles, &item_type) && num_bottles < quantity) || 
	(StringIsEqualTo(&rattles, &item_type) && num_rattles < quantity) || 
	(StringIsEqualTo(&diapers, &item_type) && num_diapers < quantity) || 
	(custom1_taken == true && StringIsEqualTo(&custom1, &item_type) && num_custom1 < quantity) ||
	(custom2_taken == true && StringIsEqualTo(&custom2, &item_type) && num_custom2 < quantity)) {
		printf("Sorry, ");
		StringPrint(&customer);
		printf(", we only have ");
		if (StringIsEqualTo(&bottles, &item_type)) {
			printf("%d ", num_bottles);
		} else if (StringIsEqualTo(&rattles, &item_type)) {
			printf("%d ", num_rattles);
		} else if (StringIsEqualTo(&diapers, &item_type)) {
			printf("%d ", num_diapers);
		} else if (custom1_taken == true && StringIsEqualTo(&custom1, &item_type)) {
			printf("%d ", num_custom1);
		} else if (custom2_taken == true && StringIsEqualTo(&custom2, &item_type)) {
			printf("%d ", num_custom2);
		}
		StringPrint(&item_type);
		printf("\n");
		StringDestroy(&item_type);
		StringDestroy(&customer);
		StringDestroy(&bottles);
		StringDestroy(&rattles);
		StringDestroy(&diapers);		
		return;
	}

	// If we make it here, there is enough inventory
	
	// Create customer if doesn't exist
	bool new_customer = true;
	Customer* current_c;

	for (int i = 0; i < num_customers; i++) {
		Customer* c = &(customers[i]);

		if (StringIsEqualTo(&((*c).name), &customer)) {
			new_customer = false;
			current_c = c;
		}
	}
	if (new_customer == true) {
		Customer new_c;
		new_c.name = StringDup(&customer);
		new_c.bottles = 0;
		new_c.diapers = 0;
		new_c.rattles = 0;
		new_c.custom1 = 0;
		new_c.custom2 = 0;
		customers[num_customers] = new_c;
		current_c = &(customers[num_customers]);
		num_customers++;
	}

	// update customer info and inventory
	if (StringIsEqualTo(&item_type, &bottles)) {
		(*current_c).bottles += quantity;
		num_bottles -= quantity;
	} else if (StringIsEqualTo(&item_type, &rattles)) {
		(*current_c).rattles += quantity;
		num_rattles -= quantity;
	} else if (StringIsEqualTo(&item_type, &diapers)) {
		(*current_c).diapers += quantity;
		num_diapers -= quantity;
	} else if (StringIsEqualTo(&item_type, &custom1)) {
		(*current_c).custom1 += quantity;
		num_custom1 -= quantity;
	} else if (StringIsEqualTo(&item_type, &custom2)) {
		(*current_c).custom2 += quantity;
		num_custom2 -= quantity;
	}

	// deallocate
	StringDestroy(&item_type);
	StringDestroy(&customer);
	StringDestroy(&bottles);
	StringDestroy(&rattles);
	StringDestroy(&diapers);	
}

void processInventory(void) {
	bottles = StringCreate("Bottles");
	rattles = StringCreate("Rattles");
	diapers = StringCreate("Diapers");

	String item_type;
	int quantity;
	
	// read args
	readString(&item_type);
	readNum(&quantity);

	// update inventory
	if (StringIsEqualTo(&bottles, &item_type)) { // bottles
		num_bottles += quantity;
	} else if (StringIsEqualTo(&rattles, &item_type)) { // rattles
		num_rattles += quantity;
	} else if (StringIsEqualTo(&diapers, &item_type)) { // diapers
		num_diapers += quantity;
	} else if (custom1_taken == true && StringIsEqualTo(&custom1, &item_type)) {
		num_custom1 += quantity;
	} else if (custom2_taken == true && StringIsEqualTo(&custom2, &item_type)) {
		num_custom2 += quantity;
	} else { // invalid item
		printf("ERROR: item doesnt exist.\n");
	}

	// deallocate
	StringDestroy(&item_type);
	StringDestroy(&bottles);
	StringDestroy(&rattles);
	StringDestroy(&diapers);
}

void processSKU(void) {
	String item_type;
	readString(&item_type);	
	if (custom1_taken == false) {
		custom1 = StringDup(&item_type);
		custom1_taken = true;
	} else {
		custom2 = StringDup(&item_type);
		custom2_taken = true;
	}
	StringDestroy(&item_type);
}


