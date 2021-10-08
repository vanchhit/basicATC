

#include <iostream.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <conio.h>

#define SIZE 20

struct time{
	int hh,mm;
};

struct date
{
	int dd,mm,yyyy;
}currdate = {24,1,2020};

class Admincontrol
{
public:
	void display();
	void addflight();
	int statuscheck();
	char* checkcallsign();
protected:
	char flightno[7];

	time t;
	date d;
	char status;
	char airline[4];
	char aircraft[5];
};

void Admincontrol::display()
{
	cout<<"\nFlight No : "<<flightno;
	if(status=='A')
	{
		cout<<"\nStatus : Arrival";
		cout<<"\nTime of Arrival is -- ";
	}
	else if(status=='D')
	{
		cout<<"\nStatus : Departure";
		cout<<"\nTime of Departure is -- ";
	}
	cout<<"\t"<<t.hh<<" : "<<t.mm;
	cout<<"\t"<<d.dd<<"/"<<d.mm<<"/"<<d.yyyy;
	cout<<"\nAirline : "<<airline;
	cout<<"\nAircraft : "<<aircraft;
}

void Admincontrol::addflight()
{
	char choice;
	cout<<"\nFlight No : ";
	gets(flightno);
	do{
		cout<<"\nEnter the status : Arriving (A) or Departing(D) : ";
		cin>>choice;
		if(toupper(choice)=='A')
			status='A';
		else if(toupper(choice)=='D')
			status='D';
	}while(toupper(choice)!='A' && toupper(choice)!='D');

	cout<<"\nEnter the date of Departure/Arrival : Year (YYYY) : ";
	cin>>d.yyyy;
	cout<<"Month (MM) : ";
	cin>>d.mm;
	cout<<"Date (DD) : ";
	cin>>d.dd;

	cout<<"\nEnter the time of Departure/Arrival (24-hour format) : Hours (HH) : ";
	cin>>t.hh;
	cout<<"Minutes (MM) : ";
	cin>>t.mm;

	cout<<"\nAirline (IATA Code) : ";
	gets(airline);
	cout<<"Aircraft (4-digit Codec) : ";
	gets(aircraft);
}

int Admincontrol::statuscheck()
	{return status;}

char* Admincontrol::checkcallsign()
	{return flightno;}

class ATCcontrol : private Admincontrol
{
public:
	void retrievedata();
	date returndate();
	int returnstatus();
};

void ATCcontrol::retrievedata()
{
	cout<<"\n\nFlight No : "<<flightno;
	if(status=='A')
	{
		cout<<"\nStatus : Arrival";
		cout<<"\nTime of Arrival is -- ";
	}
	else if(status=='D')
	{
		cout<<"\nStatus : Departure";
		cout<<"\nTime of Departure is -- ";
	}
	cout<<'\t'<<t.hh<<" : "<<t.mm;
	cout<<'\t'<<d.dd<<"/"<<d.mm<<"/"<<d.yyyy;
	cout<<"\nAirline : "<<airline;
	cout<<"\nAircraft : "<<aircraft;
}

int ATCcontrol::returnstatus()
	{return status;}

date  ATCcontrol::returndate()
	{return d;}

int datecheck(date d1,date d2)
{
	int result=1;
	if(d1.yyyy==d2.yyyy)
	{
		if(d1.mm==d2.mm)
		{
			if(d1.dd==d2.dd)
				result=0;
		}
	}
	return result;
}

void userdisp(char ch)
{
	fstream readfile;
	readfile.open("ATC.dat",ios::in|ios::binary);
	ATCcontrol temp;
	readfile.read((char *)&temp,sizeof(temp));
	cout<<"\nThe flights are:\n";
	do{
		if(datecheck(temp.returndate(),currdate)==0)
		{
			if(temp.returnstatus()==ch || ch=='L')
				temp.retrievedata();
		}
		readfile.read((char *)&temp,sizeof(temp));
	}while(!readfile.eof());
	readfile.close();
	cout<<"\n";
}

void loginpage();

void userinterface()
{
	clrscr();
	cout<<"Welcome to the user interface of the ATC Scheduler!"<<endl;
	char ch,choice;
	while(1)
	{
		cout<<"Do you want to see Arriving (A) or Departing flights (D) or all (L)? ";
		cin>>ch;
		ch=toupper(ch);
		userdisp(ch);
		cout<<"Press 'x' to log out!";
		cin>>choice;
		if(tolower(choice)=='x')
			loginpage();
		}
}

void admininterface()
{
	clrscr();
	cout<<"Enter the current date to continue:\nYear (YYYY) : ";
	cin>>currdate.yyyy;
	cout<<"Month (MM) : ";
	cin>>currdate.mm;
	cout<<"Date (DD) : ";
	cin>>currdate.dd;
	void show(),showall(),showp(),add(),modp(),delp(),deladd();
	while(1)
	{
		int choice;
		clrscr();
		cout<<"Enter your choice :";
		cout<<"\n\t1) Show details of all departing or all arriving planes";
		cout<<"\n\t2) Show details of all transits";
		cout<<"\n\t3) Show a particular transit";
		cout<<"\n\t4) Add new transit(s)";
		cout<<"\n\t5) Modify a particular transit";
		cout<<"\n\t6) Delete a particular transit";
		cout<<"\n\t7) Truncate pre-existing list and add a record";
		cout<<"\n\t8) Log out\t\t";
		cin>>choice;
		switch(choice)
		{
			case 1: show();
				break;
			case 2: showall();
				break;
			case 3: showp();
				break;
			case 4: add();
				break;
			case 5: modp();
				break;
			case 6: delp();
				break;
			case 7: deladd();
				break;
			case 8: loginpage();
				break;
			default: cout<<"\nEnter a valid choice";
				 break;
		}
	}
}

void show()
{
	fstream readfile;
	Admincontrol temp;
	char choice;
	cout<<"\nDo you want to check all arriving flights(a) or all departing flights(d)?\t";
	cin>>choice;
	readfile.open("ATC.DAT",ios::in | ios::binary);
	if(!readfile)
		cout<<"Error! File not found!";
	else
	{
		choice=toupper(choice);
		readfile.read((char *)&temp,sizeof(temp));
		cout<<"\nThe details are :";
		do{
			if(temp.statuscheck()==choice)
			{
				temp.display();
				cout<<"\n";
			}
			readfile.read((char *)&temp,sizeof(temp));
		}while(!readfile.eof());
		readfile.close();
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void showall()
{
	fstream readfile;
	Admincontrol temp;
	readfile.open("ATC.DAT",ios::in | ios::binary);
	if(!readfile)
		cout<<"Error! File not found!";
	else
	{
		readfile.read((char *)&temp,sizeof(temp));
		cout<<"\nThe details are :";
		do{
			temp.display();
			cout<<"\n";
			readfile.read((char *)&temp,sizeof(temp));
		}while(!readfile.eof());
		readfile.close();
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void showp()
{
	fstream readfile;
	Admincontrol temp;
	char usercallsign[7],tempcallsign[7];
	cout<<"\nEnter the flight number (callsign) to display its records : ";
	gets(usercallsign);
	readfile.open("ATC.DAT",ios::in | ios::binary);
	if(!readfile)
		cout<<"Error! File not found!";
	else
	{
		int flag=0;
		readfile.read((char *)&temp,sizeof(temp));
		cout<<"\nThe details are :";
		do{
			strcpy(tempcallsign,temp.checkcallsign());
			if(strcmpi(usercallsign,tempcallsign)==0)
			{
				temp.display();
				cout<<"\n";
				flag=1;
				break;
			}
			readfile.read((char *)&temp,sizeof(temp));
		}while(!readfile.eof());
		readfile.close();
		if(flag==0)
			cout<<"Record not found!";
		cout<<"\n";
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void add()
{
	fstream readfile,tempfile;
	Admincontrol temp,addrec;
	int num,i=1;
	long pos,numpos;
	readfile.open("ATC.DAT",ios::in | ios::binary);
	if(!readfile)
		cout<<"File not found!";
	else
	{
		cout<<"\nThe details are :";
		readfile.read((char *)&temp,sizeof(temp));
		do{
			cout<<"Record "<<i++<<endl;
			temp.display();
			readfile.read((char *)&temp,sizeof(temp));
		}while(!readfile.eof());
		readfile.seekg(ios::beg);
		cout<<"\nEnter the record number AFTER which you wish to add the new record : ";
		cin>>num;
		numpos=sizeof(Admincontrol)*num;
		tempfile.open("temp.DAT",ios::out);
		readfile.read((char *)&temp,sizeof(temp));
		do{
			tempfile.write((char *)&temp,sizeof(temp));
			pos=tempfile.tellg();
			readfile.read((char *)&temp,sizeof(temp));
		}while(pos<numpos || (!readfile.eof()));
		if(pos==numpos)
		{
			cout<<"\nEnter the new Flight records :";
			addrec.addflight();
			tempfile.write((char *)&addrec,sizeof(addrec));
			while(!readfile.eof())
			{
				tempfile.write((char *)&temp,sizeof(temp));
				readfile.read((char *)&temp,sizeof(temp));
			};
		}
		else
			cout<<"\nFlight not found!\n";
		readfile.close();
		tempfile.close();
		remove("ATC.DAT");
		rename("temp.DAT","ATC.DAT");
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void modp()
{
	fstream newfile;
	Admincontrol temp;
	char usercallsign[7],tempcallsign[7];
	long pos;
	int found;
	newfile.open("ATC.DAT",ios::in | ios::out | ios::binary);
	if(!newfile)
		cout<<"File not found!";
	else
	{
		cout<<"\nEnter the flight number for the records to be found : ";
		gets(usercallsign);
		do{
			pos=newfile.tellg();
			newfile.read((char *)&temp,sizeof(temp));
			strcpy(tempcallsign,temp.checkcallsign());
			if(strcmpi(usercallsign,tempcallsign)==0)
			{
				found=1;
				cout<<"\nThe details of the flight are :";
				temp.display();
				cout<<"\nEnter the replacement details :";
				temp.addflight();
				newfile.seekp(pos);
				newfile.write((char *)&temp,sizeof(temp));
				break;
			}
		}while(!newfile.eof());
		if(!found)
			cout<<"\nFlight not found!\n";
		newfile.close();
		cout<<"\n";
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void delp()
{
	fstream readfile,tempfile;
	readfile.open("ATC.DAT",ios::in | ios::binary);
	if(!readfile)
		cout<<"File not found!";
	else
	{
		tempfile.open("temp.dat",ios::out | ios::binary);
		Admincontrol temp;
		int found=0;
		char choice;
		char tempcallsign[7],usercallsign[7];
		cout<<"\nEnter the Flight number to be deleted : ";
		gets(usercallsign);
		readfile.read((char *)&temp,sizeof(temp));
		do{
			strcpy(tempcallsign,temp.checkcallsign());
			if(strcmpi(usercallsign,tempcallsign)==0)
			{
				found=1;
				cout<<"\nThe records are :\n";
				temp.display();
				cout<<"\nAre you sure you want to delete it? ";
				cin>>choice;
				if(toupper(choice)=='N')
					tempfile.write((char *)&temp,sizeof(temp));
			}
			else
				tempfile.write((char *)&temp,sizeof(temp));
			readfile.read((char *)&temp,sizeof(temp));
		}while(!readfile.eof());
		if(!found)
			cout<<"\nFlight not found!\n";
		readfile.close();
		tempfile.close();
		remove("ATC.DAT");
		rename("temp.dat","ATC.DAT");
	}
	char menuchoice='n';
	while(tolower(menuchoice)!='y')
	{
		cout<<"Press 'y' to go back to the menu. ";
		cin>>menuchoice;
	}
}

void deladd()
{
	fstream truncfile("ATC.DAT",ios::out|ios::trunc);
	Admincontrol temp;
	char ch;
	while(1)
	{
		cout<<"Enter the details of the flight:"<<endl;
		temp.addflight();
		truncfile.write((char *)&temp,sizeof(temp));
		cout<<"Do you wish to add more records? (Y/N) ";
		cin>>ch;
		if(tolower(ch)=='n')
			break;
	}
}

struct LoginDetails
{
	char Username[SIZE],Password[SIZE];
};

int logincheck(char* user, char* pass)
{
	int result=0;
	ifstream log("Logindetails.DAT");
	LoginDetails temp;
	log.read((char *)&temp,sizeof(temp));
	do{
		if(strcmpi(user,temp.Username)==0)
		{
			if(strcmpi(pass,temp.Password)==0)
			{
				result=1;
				cout<<result;
				break;
			}
		}
		log.read((char *)&temp,sizeof(temp));
	}while(!log.eof());
	return result;
}


void AdminLogin()
{
	clrscr();
	char username[SIZE],password[SIZE];
	while(1)
	{
		cout<<"Welcome to the ATC Control.\nPlease enter your Username: ";
		gets(username);
		cout<<"Password: ";
		gets(password);
		if(logincheck(username,password))
			admininterface();
		else
			cout<<"Wrong username or password!\n";
	}
}

void loginpage()
{
	clrscr();
	int ch;
	while(1)
	{
		clrscr();
		cout<<"\t\t\tWelcome to the ATC Scheduler!\nEnter your choice:\n1) Admin Login\n2) User Login\nPress any other number to exit!\n";
		cin>>ch;
		if(ch==1)
			AdminLogin();
		else if(ch==2)
			userinterface();
		else
			exit(0);
	}

}

void main()
{
	clrscr();
	loginpage();
}
