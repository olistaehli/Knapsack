// A 0/1 knapsack problem (dynamic programming) for Quantumscape
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <algorithm>
#include <iostream>
#include "battery.h"

int prices[3] = {0};
const int CAPACITIES[] = {1, 7, 5};
//Enter the budget
const int BUDGET = 100;
//Enter the capacities of the diffrent cells into the array CAPACITIES
//Enter how many cells you would like to analyze
const int TYPES[] = {1, 2, 3};
std::list<Battery> batteryList;

/** ----------------------------------------------------------
* \fn input
* \
--------------------------------------------------------------*/
int input()
{
  //Enter the prices of the batteries
  printf("\nWith which cells do you equip your customized electrocar? The budget is limited to 100 USD and the capacity should be optimized accordingly.\n\n");
  printf("Enter the material costs of the following batteries: \n\n");
  printf("Batterycell 1 (%dAh)\n", CAPACITIES[0]);
  printf("Price: ");
  scanf("%d", &prices[0]);
  printf("Batterycell 2 (%dAh)\n", CAPACITIES[1]);
  printf("Price: ");
  scanf("%d", &prices[1]);
  printf("Batterycell 3 (%dAh)\n", CAPACITIES[2]);
  printf("Price: ");
  scanf("%d", &prices[2]);
  return 0;
}

/** ----------------------------------------------------------
* \fn algorithm
* \
--------------------------------------------------------------*/
int algorithm()
{
  int dataArray[3+1][BUDGET] = {0};
  //These two numbers are needed to determine the used batteries
  int highestCapacity = 0;
  int bestBudget = 0;

  std::list<Battery>::iterator it;

  //loops through every Battery
  for(it=batteryList.begin(); it!=batteryList.end(); ++it)
  {
    int actualPrice = it->getPrice();
    int actualCapacity = it->getCapacity();
    int type = it->getType();
    // //debug prints
    // printf("actualPrice: %d\n", actualPrice);
    // printf("actualCapacity: %d\n", actualCapacity);
    // printf("type: %d\n", type);

    //loops through every number from 1 to 100
    for(int actualBudget=1; actualBudget<=BUDGET; actualBudget++)
    {
      if(actualPrice <= actualBudget)
      {
        dataArray[type][actualBudget]= std::max(dataArray[type-1][actualBudget],
        actualCapacity + dataArray[type-1][actualBudget - actualPrice]);
      }
      else
      {
        dataArray[type][actualBudget]= dataArray[type-1][actualBudget];
      }
      if(dataArray[type][actualBudget]>highestCapacity)
      {
        highestCapacity = dataArray[type][actualBudget];
        bestBudget = actualBudget;
      }
      // //debug print to get all the calculated results of capacities
      // printf("Capacity: %d\n", dataArray[type][actualBudget]);
    }
  }
  printf("\nHighest Capacity: %dAh\n", highestCapacity);
  printf("Best Budget: %d USD\n", bestBudget);

  //detect highest capacity
  int markedTypes[3] = {0};
  for(it=batteryList.end(); bestBudget>0 && it!=batteryList.begin();)
  {
    it--;
    int actualPrice = it->getPrice();
    int type = it->getType();
    if (dataArray[type][bestBudget] != dataArray[type-1][bestBudget])
    {
      markedTypes[type-1] = type;
      bestBudget = bestBudget - actualPrice;
    }
  }
  //This prints which types of cells make the perfect combination
  printf("Batterycell 1: %d\nBatterycell 2: %d\nBatterycell 3: %d\n\n", markedTypes[0], markedTypes[1], markedTypes[2]);
 return 0;
}

  /** ----------------------------------------------------------
  * \fn main
  * \
  --------------------------------------------------------------*/
int main()
  {
    //This function desplays the text and scans the input in the terminal
    input();

    //Create a list of batteries
    for(int i=0; i<3; i++)
    {
      batteryList.push_back(Battery(prices[i], CAPACITIES[i], TYPES[i]));
    }

    //This function solves the mathematical problem
    algorithm();

    //Delete the list of batteries
    for(int i=0; i<3; i++)
    {
      batteryList.pop_back();
    }
    return 0;
  }
