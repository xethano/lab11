#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



typedef struct employee
{
	char name[100];
	char title;
	double hours_worked;
	double payrate;
	double payment;
}Employee;

Employee payroll[200];

//for B, overtime is when hours_worked > 40
//hourly rate is multiplied by 1.5

//for M, overtime is when hours_worked > 40
//hourly rate is multiplied by 1.8

int main()
{
	double average_payment = 0;
	double total_payment = 0;
	double max_payment = 0;
	double min_payment = 0;
	FILE* inputfile = fopen("payroll.txt", "r");
	FILE* outputfile = fopen("output.txt", "w");
	int employee_num = 0;
	char buffer[256];
	while (!feof(inputfile))
	{
		fgets(buffer, 256, inputfile);
		strcpy(payroll[employee_num].name, buffer);
		fgets(buffer, 256, inputfile);
		payroll[employee_num].title = buffer[0];
		fgets(buffer, 256, inputfile);
		double totalhoursworked = atof(buffer);
		payroll[employee_num].hours_worked = totalhoursworked;
		fgets(buffer, 256, inputfile);
		double hourly_rate = atof(buffer);
		payroll[employee_num].payrate = hourly_rate;

		double overtime_rate;
		if (payroll[employee_num].title == 'B')
		{
			overtime_rate = 1.5;
		}
		else
		{
			overtime_rate = 1.8;
		}
		
		double regularhours = totalhoursworked;
		double overtimehours = 0;

		if (totalhoursworked > 40)
		{
			overtimehours = totalhoursworked - 40;
			regularhours = 40;
		}

		double regularpay = regularhours * hourly_rate;
		double overtimepay = overtimehours * hourly_rate * overtime_rate;
		payroll[employee_num].payment = regularpay + overtimepay;

		if (employee_num == 0)
		{
			max_payment = payroll[employee_num].payment;
			min_payment = payroll[employee_num].payment;
		}
		else
		{
			if (payroll[employee_num].payment > max_payment)
			{
				max_payment = payroll[employee_num].payment;
			}
			if (payroll[employee_num].payment < min_payment)
			{
				min_payment = payroll[employee_num].payment;
			}
		}

		employee_num++;

	}

	
	for (int i = 0; i < employee_num; i++)
	{
		total_payment += payroll[i].payment;
	}

	average_payment = total_payment / employee_num;

	fprintf(outputfile, "The total payment is $%.2lf\n", total_payment);
	fprintf(outputfile, "The average pay per employee is $%.2lf\n", average_payment);
	fprintf(outputfile, "The smallest payment was $%.2lf\n", min_payment);
	fprintf(outputfile, "The largest payment was $%.2lf\n", max_payment);

	fclose(inputfile);
	fclose(outputfile);

	

}
