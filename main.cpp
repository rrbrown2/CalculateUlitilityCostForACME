/*
 * Calculates Utility Cost for ACME UTILITY COMPANY. Customers are billed  depending on the type of customer they are.
   commerical, residential, or government.
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
using namespace std;

// function prototype
double commercial_customer(double k); // The functions will receive the amount of kw made to calcululate.
double government_customer(double k);
double residential_customer(double k);
double surcharge = 0;
double total_utility_charge = 0;
double customer_charge = 0;
ifstream infile;
ofstream outputfile;
int main()
{
    char customer_type = ' ';
    double kilowatt;
    double account_number;
    double total_surcharge = 0;
    double total_kilowatt = 0;
    double total_utility = 0;

    //creates or opens read and write files
    infile.open("read.txt");
    if (!infile.is_open())
    { //check to make sure there is an open file, if no file is open program terminates
        cout << "Read file not open";
        exit(EXIT_FAILURE);
    }

     else
    {
        cout << "Read file open" << endl;
    }

    outputfile.open("write.txt");
    if(!outputfile.is_open()) // check if output file is open
    {
         cout << "Write file is not open";
         outputfile.close();
         return 0;
    }
    else
    {
        cout << "Write file open" << endl;
    }
    //Output Header
    outputfile << "Account#\tAccount Type\tKilo-Wats Used\tSurcharge\tUtility cost\n";

    //while there is input
    while (infile >> customer_type >> kilowatt >> account_number  )
    {
            if (infile.fail()) // used to validate data in the file
            {
              infile.clear(); // used to avoid reading the same line over and over again
              continue; // then go to the next line
            }
            customer_type = toupper(customer_type); // always puts customer type in uppercase

            outputfile << setprecision(0) << fixed << noshowpoint << account_number << "\t"; //print the account number & tab

            if(account_number < 0) // checks if account number is negative
            {
                outputfile << "Account number cannot be less than 0";
                exit(0);
            }
            switch(customer_type) // Depends on the type of client call the function..
            {
               case 'C':
                    commercial_customer(kilowatt); //Return the surcharge and store in alocal variable
                    outputfile << "COM\t"; // Print the type of the client in the file
                    break;
               case 'R':
                    residential_customer(kilowatt);
                    outputfile << "RES\t"; // Print the type of the client in the file
                    break;
               case 'G':
                    government_customer(kilowatt);
                    outputfile << "GOV\t"; // Print the type of the client in the file
                     break;

                default:
                  continue;
            }

            //Print the remaining columns, kilowatt, surcharge
            outputfile << setprecision(2) << fixed << showpoint;
            outputfile << kilowatt << "\t" << surcharge << "\t\t"<< customer_charge << endl;

            total_kilowatt += kilowatt; // Add the current values to the totals
            total_surcharge += surcharge;
            total_utility += total_utility_charge;

    } // end of while loop

    //Print the totals
    outputfile << endl << "\tTOTALS:\t" << total_kilowatt << "\t" << total_surcharge << "\t\t" << total_utility;

    //close files
    outputfile.close();
    infile.close();
    return 0;
}

double commercial_customer(double k)
{

    double charge;
    if( k < 0) // if kilowats is less than zero program should not continue
    {
       outputfile << "Kilowats cannot be negative";
       outputfile.clear();
       exit(0);
    }
    if (k <= 999)
    {
       charge = 0.22 * k;
       surcharge = 0;
       customer_charge = charge;
       total_utility_charge = charge;
    }
    else if (k <= 1999)
    {
       charge = (0.22 * 999) + (0.29 * (k - 999));
       surcharge = 0;
       customer_charge = charge;
       total_utility_charge = charge;
    }

    else
    {
       charge = (0.22 * 999) + (0.29 * 1000) + (0.45 * (k - 1999)) + 100;
       if(k > 2000)
       surcharge = 100;
       customer_charge = charge;
       total_utility_charge = charge;
    }
   	return charge;

}

double government_customer(double k)
{
    surcharge = 0;
    double charge;
    if( k < 0) // if kilowats is less than zero program should not continue
    {
        outputfile << "Kilowats cannot be negative";
        outputfile.clear();
        exit(0);
    }
    if (k <= 1500)
    { //If less than 1500 only multiply the kilowatts by 0.34
   	   charge = 0.34 * k;
           customer_charge = charge;
           total_utility_charge = charge;
    }
    else if (k <= 2500)
    { //If less than 2500 the first 1500 x 0.34 and the remaining at 0.30
       charge = (0.34 * 1500) + (0.30 * (k - 1500));
      customer_charge = charge;
       total_utility_charge = charge;
    }
    else
    { // if charge is greater than 2500, charge the first 1500 kw at 0.34, the next 1000 (to up 2500) at 0.30 and the remain kw plus 0.25
        charge = (0.34 * 1500) + (0.30 * 1000) + (0.25 * (k - 2500));
        customer_charge = charge;
        total_utility_charge = charge;
    }
   	return charge;
}

double residential_customer(double k)
{
        surcharge = 0;
 	double charge;
        if( k < 0) // if kilowats is less than zero program should not continue
        {
            outputfile << "Kilowats cannot be negative";
            outputfile.clear();
            exit(0);
        }
 	if (k <= 500)
        { //If k less than 500 only multiply the kilowatts by 0.25
   	   charge = 0.25 * k;
           customer_charge = charge;
           total_utility_charge = charge;
        }
        else
        { // if is greater than 500, charge the first 500 kw at 0.25 and add the remain kw plus 0.35
            charge = (0.25 * 500) + (0.35 * (k - 500));
            customer_charge = charge;
            total_utility_charge = charge;
        }
   	return charge;
}


