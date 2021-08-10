// header files
#include<stdio.h>                // stdio for input and output operations
#include<string.h>               // string for string operations
#include<stdlib.h>               // stdlib for clearing screen using system("cls") function
#include<time.h>	             // time to calculate time elapsed between rent and return


//creating custom data type bool to hold two values - true or false
#define true 1
#define false 0
#define bool int



//declaring global variables used throughout the program to minimize runtime 

int converter=1;                 //THIS VARIABLE IS USED TO SET TIME CONVERTER VALUES
								 //for example, if it is 1, 1 second in real life = 1 day in the program
								 //if it is 60, 60 seconds in real life is 1 day in the program


int C_counter = 0;			     //counts number of accounts created

char gvar;						 //hollow variable to ensure getch() does not encounter compiler related errors

int Vlim = 10;					 //Number of vehicles in catalogue

char mch;                        //

int noose;                       //No. of seconds between rent and return

int price;						 //To calculate total amount after returning 



//CUSTOMER INFORMATION STRUCTURE
struct Customer_info
{
	int C_number;
	char C_username[50];
	char C_email[100];
	float P_number;
	bool Rent;//to check if they have currently rented a vehicle or not
	int match;//to handle group booking
}customer[25];                   //up to 25 users at a time


//VEHICLE INFORMATION STRUCTURE
struct Vehicle_info
{
	int V_number;
	bool Assigned;//to check if vehicle is currently in use
	char V_name[50];
	char V_company[50];
	char V_type[10];
	int CPD;//cost
	int vmatch;//to handle group bookings
	time_t timehold;
}V[15];



//function to check if the entered username matches any username in the list of accounts
int Login_check(char username[100])
{

	for (int i = 0; i < C_counter; i++)
	{
		if (strcmp(username, customer[i].C_username) == 0)
			return customer[i].C_number;
	}

	return -1;

}



//function to get data of new account and increment necessary pointers
void Add_Customer()
{
	printf("\n Enter Username : ");
	scanf("%s",customer[C_counter].C_username);
	printf("\n Enter email id : ");
	scanf("%s",customer[C_counter].C_email);
	printf("\n Enter Phone No : ");
	scanf("%f", &customer[C_counter].P_number);
	printf("\n Your Customer Number has been assigned as : %d\n ",C_counter);
	customer[C_counter].Rent = false;
	getch(gvar);
}



//function to display list of vehicles 
void Display_cat()
{
	system("cls");
	printf("\n Vehicle Catalogue : \n");
	for (int i = 0; i < Vlim; i++)
	{
		printf("\n No. %d ", V[i].V_number);
		printf("   %s ", V[i].V_name);
		printf(" (%s) ,", V[i].V_company);
		printf("\n %s ", V[i].V_type);
		printf("\n Rent cost per day : %d , ", V[i].CPD);
		printf("\n Status : %s ", (V[i].Assigned == false) ? "Available" : "Unavailable");
		printf("\n");
	}
}



//MAIN FUNCTION
void main()
{


	//MOST VARIABLES IN MAIN ARE DECLARED HERE
	//(the menu system uses labels, and several compilers don't allow declarations after labels to save runtime data)
	int current_cust;                //this holds the number of the customer currently being served
	char utemp[100];

	int temp,temp1,temp2;
	int atemp[25];
	int i,a;
	//all other variables are temporary holders

	//time variable to get the number of seconds since 1970
	time_t next;



	//INITIALISING VEHICLE INFORMATION
	V[0].V_number = 101;
	strcpy(V[0].V_name,"Honda City ZX");
	strcpy(V[0].V_company,"Honda");
	strcpy(V[0].V_type,"Sedan");
	V[0].CPD = 1000;
	V[0].Assigned = false;


	V[1].V_number = 102;
	strcpy(V[1].V_name, "Skoda Superb");
	strcpy(V[1].V_company, "Skoda");
	strcpy(V[1].V_type, "Sedan");
	V[1].CPD = 1200;
	V[1].Assigned = false;


	V[2].V_number = 103;
	strcpy(V[2].V_name, "Hyundai Verna");
	strcpy(V[2].V_company, "Hyundai");
	strcpy(V[2].V_type, "Sedan");
	V[2].CPD = 1300;
	V[2].Assigned = false;


	V[3].V_number = 104;
	strcpy(V[3].V_name, "Hyundai elite i20");
	strcpy(V[3].V_company, "Hyundai");
	strcpy(V[3].V_type, "Hatchback");
	V[3].CPD = 500;
	V[3].Assigned = false;


	V[4].V_number = 105;
	strcpy(V[4].V_name, "Tata Tiago");
	strcpy(V[4].V_company, "Tata");
	strcpy(V[4].V_type, "Hatchback");
	V[4].CPD = 350;
	V[4].Assigned = false;

	V[5].V_number = 106;
	strcpy(V[5].V_name, "BMW 3 series");
	strcpy(V[5].V_company, "BMW");
	strcpy(V[5].V_type, "Luxury");
	V[5].CPD = 4500;
	V[5].Assigned = false;


	V[6].V_number = 107;
	strcpy(V[6].V_name, "Jaguar XE");
	strcpy(V[6].V_company, "Jaguar");
	strcpy(V[6].V_type, "Luxury");
	V[6].CPD = 6200;
	V[6].Assigned = false;


	V[7].V_number = 108;
	strcpy(V[7].V_name, "Lexus Ls");
	strcpy(V[7].V_company, "Lexus");
	strcpy(V[7].V_type, "Luxury");
	V[7].CPD = 9000;
	V[7].Assigned = false;

	V[8].V_number = 109;
	strcpy(V[8].V_name, "Kia Seltos");
	strcpy(V[8].V_company, "Kia");
	strcpy(V[8].V_type, "SUV");
	V[8].CPD = 4000;
	V[8].Assigned = false;

	V[9].V_number = 110;
	strcpy(V[9].V_name, "Hyundai Creta");
	strcpy(V[9].V_company, "Hyundai");
	strcpy(V[9].V_type, "SUV");
	V[9].CPD = 5000;
	V[9].Assigned = false;

	V[0].vmatch = -1;
	V[1].vmatch = -1;
	V[2].vmatch = -1;
	V[3].vmatch = -1;
	V[4].vmatch = -1;
	V[5].vmatch = -1;
	V[6].vmatch = -1;
	V[7].vmatch = -1;
	V[8].vmatch = -1;
	V[9].vmatch = -1;

	system("cls");

	//title screen

	printf("\n Mini project :\n");
	printf("\n CAR RENTAL SYSTEM\n\n\n");

	printf("\n Done by \n");
	printf("\n 191CV151	Suhas S N\n 191CV101	Aadhav R Subramanian\n 191CV222	Keshav Kumar Meena\n 191MN004	Ashutosh Kumar\n");
	printf("\n\n\n Press any key to begin ");

	getch(gvar);


	//login menu label 


login:


	system("cls");


	//menu
	printf("\n\n 1. Login with username");
	printf("\n\n 2. Create new account");
	printf("\n\n 3. Exit");

	printf("\n\n\n Enter your choice : ");
	scanf("%c", &mch);

	//switch function for login menu
	switch(mch)
	{
	case '1' : 

		//login
		system("cls");
		printf("\n Enter your username : ");
		scanf("%s",utemp);
		if (Login_check(utemp) == -1)
		{
			printf("\n Invalid Username...");
			getch(gvar);
			goto login;
		}
		else
		{
			current_cust = Login_check(utemp);
			printf("\n Login Successful.");
			getch(gvar);
		}
		system("cls");
		break;

	case '2' :
		//signup
		system("cls");
		Add_Customer();
		C_counter++;
		goto login;

	case '3' :
		//exit
		exit(0);

	default:
		goto login;
	}




	//customer action menu label
	cmenu:


	//menu
		system("cls");
		printf("\n\n Choose an action : \n\n");
		printf("\n\n 1. Rent a vehicle");
		printf("\n\n 2. Group booking");
		printf("\n\n 3. Reserve a vehicle");
		printf("\n\n 4. Return Vehicle");
		printf("\n\n 5. Logout");
		printf("\n\n\n Enter your choice : ");

		switch (getch())
		{

		case '1':
			//rent
			system("cls");
			
			//checking if user has already rented/reserved anything
			if (customer[current_cust].Rent == true)
			{
				printf("\n You must return your current vehicle to rent a new one..");
				getch(gvar);
				goto cmenu;
			}
			else
			{
				//showing catalogue
				Display_cat();
				printf("\n Enter the number of the vehilce you want to rent : ");
				scanf("%d", &temp);
				if (temp<100||temp>110)
				{
					printf("\n Invalid number...");
					getch(gvar);
					goto cmenu;
				}
				customer[current_cust].Rent = true;
				temp = temp % 100;
				temp--;
				//checking if vehicle is rented by other customer
				if (V[temp].Assigned == true)
				{
					printf("\n That Vehicle is unavailable...");
					getch(gvar);
					goto cmenu;
				}
				else
				{
					V[temp].Assigned = true;
					V[temp].timehold = time(NULL);
					system("cls");
					printf("\n The vehicle has been rented,\n The price will be calculated as follows : ");
					printf("\n Number of days * %d", V[temp].CPD);
					printf("\n A receipt will be sent to your email after you return the vehicle\n\n Thank you for choosing us ");
					getch(gvar);
					system("cls");
					customer[current_cust].match = V[temp].V_number;
				}
				goto cmenu;
			}
		case '2':
			//group booking
			//checking if user has already rented/reserved anything
			system("cls");
			if (customer[current_cust].Rent == true)
			{
				printf("\n You must return your current vehicle to rent a new one..");
				getch(gvar);
				goto cmenu;
			}
			else
			{
				printf("\n Enter the number of vehicles you want to book : ");
				scanf("%d", &temp);
				system("cls");
				Display_cat();
				printf("\n Enter the numbers of the vehicles you want to rent : \n");

				for (i = 0; i < temp; i++)
				{
					printf(" ");
					scanf("%d", &atemp[i]);
					if (atemp[i] < 100 || atemp[i]>110)
					{
						printf("\n Invalid number...");
						getch(gvar);
						goto cmenu;
					}
				}
				customer[current_cust].Rent = true;
				for (i = 0; i < temp; i++)
				{
					atemp[i] %= 100;
					atemp[i]--;
					//checking if vehicle is rented by other customer
					if (V[atemp[i]].Assigned == true)
					{
						printf("\n Some vehicle(s) is unavailable...");
						getch(gvar);
						goto cmenu;
					}
				}
				temp1 = 0;
				for (i = 0; i < temp; i++)
				{
					V[atemp[i]].Assigned = true;
					V[atemp[i]].timehold = time(NULL);
					V[atemp[i]].vmatch = customer[current_cust].C_number;
					temp1 += V[atemp[i]].CPD;
				}
				system("cls");
				printf("\n\n The vehicles have been rented,\n\n The price will be calculated as follows : ");
				printf("\n\n Number of days * %d", temp1);
				printf("\n\n A receipt will be sent to your email after you return the vehicles\n\n Thank you for choosing us ");
				getch(gvar);
				system("cls");
			}
			goto cmenu;

		case '3':
			//reserving a vehicle for reduced price
			system("cls");
			//checking if user has already rented/reserved anything
			if (customer[current_cust].Rent == true)
			{
				printf("\n You must return your current vehicle to reserve one..");
				getch(gvar);
				goto cmenu;
			}
			else
			{
				Display_cat();
				printf("\n Enter the number of the vehilce you want to reserve : ");
				scanf("%d", &temp);
				if (temp < 100 || temp>110)
				{
					printf("\n Invalid number...");
					getch(gvar);
					goto cmenu;
				}
				customer[current_cust].Rent = true;

				temp %= 100;
				temp--;
				//checking if vehicle is rented by other customer
				if (V[temp].Assigned == true)
				{
					printf("\n That Vehicle is unavailable...");
					getch(gvar);
					goto cmenu;
				}
				else
				{
					V[temp].Assigned = true;
					V[temp].timehold = time(NULL);
					system("cls");
					printf("\n\n The vehicle has been reserved,\n\n The price will be calculated as follows : ");
					printf("\n\n Number of days * %d", V[temp].CPD / 10);
					printf("\n\n A receipt will be sent to your email after you return the vehicle\n\n Thank you for choosing us ");
					getch(gvar);
					system("cls");
					customer[current_cust].match = V[temp].V_number;
					goto cmenu;
				}

			}

		case '4':
			//returning vehicle(s)
			system("cls");

			//checking if user has rented any vehicle
			if (customer[current_cust].Rent == false)
			{
				printf("\n You must rent or reserve a vehicle to return one...");
				getch(gvar);
				goto cmenu;
			}
			else

				//returning all rented vehicles of user and calculating price
			{
				temp1 = 0;
				customer[current_cust].Rent = false;
				for (i = 0; i < Vlim; i++)
				{
					if (customer[current_cust].match == V[i].V_number || customer[current_cust].C_number==V[i].vmatch)
					{
						V[i].Assigned = false;
						temp1 += V[i].CPD;						
						V[i].vmatch = -1;

						//time calculator
						next = time(NULL);
						noose = -1*(V[i].timehold - next);
					}
				}

				noose /= converter;
				printf("\n\n Returned Successfully");
				printf("\n\n Cost : DAYS * RATE : %d * %d : %d\n", noose, temp1, noose * temp1);
				printf("\n\n A receipt has been sent to \n\n %s \n\n regarding transatcion details\n\n\n Thank you for your business with us\n", customer[current_cust].C_email);
				getch(gvar);
				goto cmenu;
			}

		case '5':
			//go back
			goto login;

		default:
			goto cmenu;
		}

	
	//END OF PROGRAM

}


