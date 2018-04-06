#ifndef _BATTERY_H_
#define _BATTERY_H_

/* ============================ Class declaration =========================== */
class Battery
{
public:
	//Constructor and Destructor
	Battery(int price, int capacity, int type)
	{
		this->price = price;
		this->capacity = capacity;
		this->type = type;
	}
	~Battery(){}

	//Public member functions
	int getPrice() {return price;}
	int getCapacity() {return capacity;}
	int getType() {return type;}

private:
	//Private member data
	int capacity, price, type;
};

#endif
