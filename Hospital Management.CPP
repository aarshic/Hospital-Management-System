#include<iostream.h>
#include<fstream.h>
#include<ctype.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
class patient
{
	int pat_id;                         //Patient's ID
	char name[50];                      //Patient's name
	int d,m,y;                          //Patient's Date of Birth
	char gender[1];                     //Patient's gender
	char blood_group[3];                //Patient's Blood Group
	int age;                            //Patient's age
	long int ph_no;                     //Patient's Phone no.
	char address[100];                  //Patient's address
	int ward_no;                        //Patient's Ward no.
	char M_C_P[20];                     //function to enter any
					    				//medi claim policy
	public:
		void new_record();              //function for new record
		void show_record();             //function to show record
		int gender_check(char a[]);     //function to check gender format
		void modify();                  //function to modify record
		void report();			//function to show data in tabular format
		int retpat_id();		//function to return patient's id
		int retage();			//function to return patient's age
};

void patient::new_record()
{
	int c=0;
	cout<<"\nEnter The Patient's ID : ";
	cin>>pat_id;
	cout<<"\n\nEnter The Name of The Patient : ";
	gets(name);
	while(!c)
	{
		cout<<"\n\nEnter patient's gender (M or F)  :  ";
		gets(gender);
		c=gender_check(gender);
	}
	cout<<"\n\nEnter patient's blood group  :  ";
	gets(blood_group);
	cout<<"\n\nEnter patient's Date of Birth  ->  ";
	cout<<"\nday  :  ";
	cin>>d;
	cout<<"month  :  ";
	cin>>m;
	cout<<"year  :  ";
	cin>>y;
	cout<<"\n\nEnter patient's age  :   ";
	cin>>age;
	cout<<"\n\nEnter patient's phone no.  :  ";
	cin>>ph_no;
	cout<<"\n\nEnter patient's address  :  ";
	gets(address);
	cout<<"\n\nEnter patient's ward no.  :  ";
	cin>>ward_no;
	cout<<"\n\nName of the medi claim policy (if any)  :  ";
	gets(M_C_P);
	cout<<"\n\n\nRecord saved.....";
}

int patient::gender_check(char a[])
{
	if((a[0]=='m')||(a[0]=='f')||(a[0]=='M')||(a[0]=='F')&&(a[1]=='\0'))
	 {
		return 1;
	 }
	else
	 {
		cout<<"\n\nINCORRECT INPUT!!! TRY AGAIN!!!\n";
		return 0;
	 }
}



void patient::show_record()
{
	cout<<"\nPatient's name  :  ";
	puts(name);
	cout<<"\nPatient's ID  :  "<<pat_id;
	cout<<"\nPatient's gender  :  ";
	puts(gender);
	cout<<"\nPatient's blood group  :  ";
	puts(blood_group);
	cout<<"\nPatient's Date of Birth  ->  "<<"\ndata  :  "<<d<<"\tmonth  :  "<<m<<"\tyear  :  "<<y;
	cout<<"\nPatient's age  :   "<<age;
	cout<<"\nPatient's phone no.  :  "<<ph_no;
	cout<<"\nPatient's address  :  ";
	puts(address);
	cout<<"\nPatient's ward no.  :  "<<ward_no;
	cout<<"\nMedi claim policy (if any) :  ";
	puts(M_C_P);
}

void amount()
{
	char ch;
	int n;
	cout<<"\n\nEntry fee  :  500";
	cout<<"\n\nNo. of days admitted  :  ";
	cin>>n;
	cout<<"\n\nTotal amount  :  "<<((n*1000)+500);
	cout<<"\n\nAmount paid (y/n)  :  ";
	cin>>ch;
}
void patient::modify()
{
	cout<<"\nThe Patient's ID : "<<pat_id;
	cout<<"\n\nEnter The Name of the patient : ";
	gets(name);
	cout<<"\n\nEnter patient's age  :   ";
	cin>>age;
	cout<<"\n\nEnter patient's phone no.  :  ";
	cin>>ph_no;
	cout<<"\n\nEnter patient's address  :  ";
	gets(address);
	cout<<"\n\nEnter patient's ward no.  :  ";
	cin>>ward_no;
	cout<<"\n\nName of the medi claim policy (if any)  :  ";
	gets(M_C_P);
}


void patient::report()
{
	cout<<pat_id<<setw(15)<<" "<<name<<setw(10)<<" "<<ward_no<<setw(13)<<age<<endl;
}

int patient::retpat_id()
{
	return pat_id;
}

int patient::retage()
{
	return age;
}

void write_record();		//function to write record in binary file
void display_sp(int);		//function to display patient's details
void modify_record(int);	//function to modify record
void delete_record(int);	//function to delete record
void display_all();		//function to display all patient's details
void intro();			//introductory screen function
void amount();

void write_record()
{
	patient p;
	ofstream outFile;
	outFile.open("pat.dat",ios::binary|ios::app);
	p.new_record();
	outFile.write((char *) &p, sizeof(patient));
	outFile.close();
}


void display_sp(int n)
{
	patient p;
	int flag=0;
	ifstream inFile;
	inFile.open("pat.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tPATIENT'S DETAILS\n";
	while(inFile.read((char *) &p, sizeof(patient)))
	{
		if(p.retpat_id()==n)
		{
			p.show_record();
			flag=1;
		}
	}
	inFile.close();
	if(flag==0)
		cout<<"\n\n\n\n\t\tRecord does not exist";
}


void modify_record(int n)
{
	int found=0;
	patient p;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(File.read((char *) &p, sizeof(patient)) && found==0)
	{
		if(p.retpat_id()==n)
		{
			p.show_record();
			cout<<"\n\nEnter The New Details of account"<<endl;
			p.modify();
			int pos=(-1)*sizeof(patient);
			File.seekp(pos,ios::cur);
			File.write((char *) &p, sizeof(patient));
			cout<<"\n\n\t Record Updated";
			found=1;
		}
	}
	File.close();
	if(found==0)
		cout<<"\n\n Record Not Found ";
}


void delete_record(int n)
{
	patient p;
	ifstream inFile;
	ofstream outFile;
	inFile.open("pat.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &p, sizeof(patient)))
	{
		if(p.retpat_id()!=n)
		{
			outFile.write((char *) &p, sizeof(patient));
		}
	}
	inFile.close();
	outFile.close();
	remove("pat.dat");
	rename("Temp.dat","pat.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	patient p;
	ifstream inFile;
	inFile.open("pat.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"PATIENT ID       NAME          WARD NO.    AGE\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	while(inFile.read((char *) &p, sizeof(patient)))
	{
		p.report();
	}
	inFile.close();
}

void intro()
{
	cout<<"\n\n\n"<<setw(43)<<"SICA SS SCHOOL";
	cout<<"\n\n\n\n\n\t\t\tHOTEL MANAGEMENT SYSTEM";
	cout<<"\n\n"<<setw(44)<<"Session : 2015-16";
	cout<<"\n\n\n\n\n\n\n\nGUIDED BY :";
	cout<<"\t\t\t\t\t\t     SUBMITTED BY :";
	cout<<"\nMR. SANJAY OJHA";
	cout<<setw(62)<<" AARSHI CHOURASIA";
	getch();
}


int main()
{
	char ch;
	int num;
	int x;
	clrscr();
	intro();
	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\tENTER PASSWORD -> ";
	char*password;
	cin>>password;
	x=strcmp(password,"SICA@78");
	if(x==0)
	 {
		cout<<"Access Granted";
	 }
	else
	 {
		cout<<"\a";
	 }
	do
	{
		clrscr();
		cout<<"\n\n\n\t\tMAIN MENU";
		cout<<"\n\n\t01. New Record";
		cout<<"\n\n\t02. Amount";
		cout<<"\n\n\t03. Show Record";
		cout<<"\n\n\t04. List of all Patients";
		cout<<"\n\n\t05. Delete Record";
		cout<<"\n\n\t06. Modify Record";
		cout<<"\n\n\t07. Exit";
		cout<<"\n\n\tSelect Your Option (1-6) ";
		cin>>ch;
		clrscr();
		switch(ch)
		{
			case '1':write_record();
				 break;
			case '2':amount();
				 break;
			case '3':cout<<"\n\n\tEnter Patient's ID : ";
				 cin>>num;
				 display_sp(num);
				 break;
			case '4':display_all();
				 break;
			case '5':cout<<"\n\n\tEnter Patient's ID : ";
				 cin>>num;
				 delete_record(num);
				 break;
			case '6':cout<<"\n\n\tEnter Patient's ID : ";
				 cin>>num;
				 modify_record(num);
				 break;
			case '7':cout<<"\n\n\n\n\n\n\n\n\n\t\t\t\tTHANK YOU";
				 break;
			default :cout<<"\a";
		}
		getch();
	}
	while(ch!='6');
	return 0;
}
