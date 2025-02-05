//---------------------------------------------------------------------------
//	PROJECT AIR TICKET RESRVATION
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	INCLUDED HEADER FILES
//---------------------------------------------------------------------------

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>


//---------------------------------------------------------------------------
//  THIS CLASS DRAW LINES, BOXES, ETC.
//---------------------------------------------------------------------------

class DRAW
{
	public :
			void LINE_HOR(int, int, int, char) ;
			void LINE_VER(int, int, int, char) ;
			void BOX(int,int,int,int,char) ;
} ;

//---------------------------------------------------------------------------
// THIS CLASS CONTROLS ALL THE FUNCTIONS RELATED TO TICKETS
//---------------------------------------------------------------------------

class TICKET
{
	public :
			void ADDITION(void) ;
			void ENQUIRY(void) ;
			char *FLIGHTNO(int) ;
	private :
			void ADD_RECORD(char[10], char[15], char[15], int, int) ;

	protected :
			char fltno[10], from[15], to[15] ;
			int ecofair, exefair ;
} ;

//---------------------------------------------------------------------------
// THIS CLASS CONTROLS ALL THE FUNCTIONS RELATED TO PASSENGERS
//---------------------------------------------------------------------------

class PASSENGER
{
	public :
			void ADD_RECORD(int, int, char[26], char[36], int, char, char) ;
			void DELETE_TICKET(int) ;
			int DELETE_FLIGHT(int) ;
			void LIST(void) ;
			int LAST_TICKETNO(void) ;
			int SEATS(int) ;
			int FOUND(int) ;
			char *NAME(int) ;
	protected :
			char Class, name[26], address[36], sex ;
			int slno, age, ticketno ;
} ;

//---------------------------------------------------------------------------
// THIS IS DERIVED CLASS WHICH CONTROLS ALL THE FUNCTIONS
// RELATED TO RESERVATION, CANCELLATION, ETC.
//---------------------------------------------------------------------------

class RESERVE : public TICKET, public PASSENGER
{
	public :
			void RESERVATION(void) ;
			void CANCELLATION(void) ;
			void DISPLAY_TICKET(void) ;
			void DELETE_ALL(void) ;
} ;

//---------------------------------------------------------------------------
// FUNCTION TO DRAW HORIZONTAL LINE
//---------------------------------------------------------------------------

void DRAW :: LINE_HOR(int coloumn1, int coloumn2, int row, char c)
{
	for (coloumn1; coloumn1<=coloumn2; coloumn1++ )
	{
		gotoxy(coloumn1,row) ;
		cout <<c ;
	}
}

//---------------------------------------------------------------------------
// FUNCTION TO DRAW VERTICAL LINE
//---------------------------------------------------------------------------

void DRAW :: LINE_VER(int row1, int row2, int coloumn, char c)
{
	for ( row1 ; row1<=row2; row1++ )
	{
		gotoxy(coloumn,row1) ;
		cout <<c ;
	}
}

//---------------------------------------------------------------------------
// FUNCION TO DRAW BOX
//---------------------------------------------------------------------------

void DRAW :: BOX(int column1, int row1, int column2, int row2, char c)
{
	char ch=218 ;
	char c1, c2, c3, c4 ;
	char c11=196, c12 = 179 ;
	if (c == ch)
	{
		c1=218 ;
		c2=191 ;
		c3=192 ;
		c4=217 ;
		c11 = 196 ;
		c12 = 179 ;
	}
	else
	{
		c1=c ;
		c2=c ;
		c3=c ;
		c4=c ;
		c11 = c ;
		c12 = c ;
	}
	gotoxy(column1,row1) ;
	cout <<c1 ;
	gotoxy(column2,row1) ;
	cout <<c2 ;
	gotoxy(column1,row2) ;
	cout <<c3 ;
	gotoxy(column2,row2) ;
	cout <<c4 ;
	column1++ ;
	column2-- ;
	LINE_HOR(column1,column2,row1,c11) ;
	LINE_HOR(column1,column2,row2,c11) ;
	column1-- ;
	column2++ ;
	row1++;
	row2--;
	LINE_VER(row1,row2,column1,c12) ;
	LINE_VER(row1,row2,column2,c12) ;

}

//---------------------------------------------------------------------------
// FUNCTION TO ADD GIVEN DATA IN THE TICKET FILE(TICKET.DAT)
//---------------------------------------------------------------------------

void TICKET :: ADD_RECORD(char t_fltno[10], char t_from[15], char t_to[15], int t_ecofair, int t_exefair)
{
	fstream file ;
	file.open("TICKET.DAT", ios::app) ;
	strcpy(fltno,t_fltno) ;
	strcpy(from,t_from) ;
	strcpy(to,t_to) ;
	ecofair = t_ecofair ;
	exefair = t_exefair ;
	file.write((char *) this , sizeof(TICKET)) ;
	file.close() ;
}

//---------------------------------------------------------------------------
// FUNCTION TO RETURN FLIGHT NO. FOR THE GIVEN S.NO
//---------------------------------------------------------------------------

char *TICKET :: FLIGHTNO(int sno)
{
	fstream file ;
	file.open("TICKET.DAT", ios ::in) ;
	int count=1 ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if (sno == count)
			break ;
		count++ ;
	}
	file.close() ;
	return fltno ;
}

//---------------------------------------------------------------------------
// FUNCTION TO GIVES DATA TO ADD RECORDS IN TICKET FILE
//---------------------------------------------------------------------------

void TICKET :: ADDITION(void)
{
	fstream file ;
	file.open("TICKET.DAT", ios::in) ;
	if (!file.fail())
		return ;
	file.close() ;
	ADD_RECORD("KL146","DELHI","MUMBAI",1500,1700) ;
	ADD_RECORD("KL146","MUMBAI","DELHI",1500,1700) ;
	ADD_RECORD("KL156","DELHI","CALCUTTA",1700,1900) ;
	ADD_RECORD("KL156","CALCUTTA","DELHI",1700,1900) ;
	ADD_RECORD("KL166","DELHI","MADRAS",2100,2300) ;
	ADD_RECORD("KL166","MADRAS","DELHI",2100,2300) ;
	ADD_RECORD("KL176","MUMBAI","CALCUTTA",1900,2100) ;
	ADD_RECORD("KL176","CALCUTTA","MUMBAI",1900,2100) ;
	ADD_RECORD("KL186","MUMBAI","MADRAS",1800,2000) ;
	ADD_RECORD("KL186","MADRAS","MUMBAI",1800,2000) ;
	ADD_RECORD("KL196","CALCUTTA","MADRAS",1600,1800) ;
	ADD_RECORD("KL196","MADRAS","CALCUTTA",1600,1800) ;
}

//---------------------------------------------------------------------------
// FUNCTION TO DISPLAY LIST OF FLIGHTS
//---------------------------------------------------------------------------

void TICKET :: ENQUIRY(void)
{
	clrscr() ;
	fstream file ;
	file.open("TICKET.DAT", ios::in) ;
	DRAW d ;
	d.BOX(1,2,80,24,218) ;
	d.LINE_HOR(2,79,4,196) ;
	d.LINE_HOR(2,79,6,196) ;
	d.LINE_HOR(2,79,22,196) ;
	textcolor(GREEN+BLINK) ;
	gotoxy(30,3) ;
	cprintf ("LIST OF THE FLIGHTS") ;
	textcolor(LIGHTGRAY) ;
	textcolor(GREEN) ;
	textbackground(WHITE) ;
	for (int i=2; i<=79; i++)
	{
		gotoxy(i,5) ;
		cprintf(" ") ;
	}
	gotoxy(2,5) ;
	cprintf(" Sno. FLIGHT NO.   FROM         TO          ECONOMIC FAIR     EXECUTIVE FAIR") ;
	textcolor(LIGHTGRAY) ;textbackground(BLACK) ;
	int row=7, sno=1 ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		gotoxy(4,row) ;
		cout <<sno ;
		gotoxy(9,row) ;
		cout <<fltno ;
		gotoxy(20,row) ;
		cout <<from ;
		gotoxy(34,row) ;
		cout <<to ;
		gotoxy(52,row) ;
		cout <<ecofair ;
		gotoxy(67,row) ;
		cout <<exefair ;
		row++ ;
		sno++ ;
	}
	file.close() ;
}

//---------------------------------------------------------------------------
// FUNCTION TO RESERVE TICKET FOR THE PASSENGER
//---------------------------------------------------------------------------

void RESERVE :: RESERVATION(void)
{
	clrscr() ;
	ENQUIRY() ;
	char t1[5], pclass, pname[26], paddress[36], psex, pfltno[10] ;
	int t2, valid, page,tno,sno ;
	PASSENGER p ;
	tno = p.LAST_TICKETNO() + 1 ;
	do
	{
		valid = 1 ;
		gotoxy(3,23) ;
		cout <<"			" ;
		gotoxy(3,23) ;
		cout <<"PRESS <ENTER> TO EXIT" ;
		gotoxy(3,20) ;
		cout <<"			";
		gotoxy(3,20) ;
		cout <<"ENTER Sno. of the FLIGHT : " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		sno = t2 ;
		if  (strlen(t1) == 0)
			return ;
		if (sno < 1 || sno >12)
		{
			valid = 0 ;
			gotoxy(3,23) ;
			cout <<"			" ;
			gotoxy(3,23) ;
			cout <<"\7ENTER CORRECTLY" ;
			getch() ;
		}
	} while (!valid) ;
	int i=1 ;
	fstream file ;
	file.open ("TICKET.DAT",ios::in);
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if (sno == i)
			break ;
		i++ ;
	}
	file.close() ;
	strcpy(pfltno,fltno) ;
	if (p.SEATS(sno) >= 250)
	{
		gotoxy(5,21) ;
		cout <<"\7Sorry! Seats are not available." ;
		getch() ;
		return ;
	}
	gotoxy(3,23) ;
	cout <<"						" ;
	gotoxy(3,23) ;
	cout <<"E=ECONOMIC, X=EXECUTIVE or PRESS <ENTER> TO EXIT" ;
	do
	{
		gotoxy(3,21) ;
		cout <<"				" ;
		gotoxy(3,21) ;
		cout <<"By which Class you want to travel : " ;
		pclass = getche() ;
		pclass = toupper(pclass) ;
		if (pclass == 13)
			return ;
	} while (pclass != 'E' && pclass !='X') ;
	clrscr() ;
	gotoxy(72,3) ;
	cout <<"<0>=EXIT" ;
	gotoxy(34,2) ;
	cout <<"RESERVATION" ;
	gotoxy(5,5) ;
	cout <<"NAME	:" ;
	gotoxy(5,6) ;
	cout <<"ADDRESS :" ;
	gotoxy(5,7) ;
	cout <<"SEX M/F :" ;
	gotoxy(5,8) ;
	cout <<"AGE	:" ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol () ;
		cout <<"ENTER NAME OFTHE PASSENGER" ;
		gotoxy(15,5) ; clreol() ;
		gets(pname) ;
		if (pname[0] == '0')
			return ;
		if (strlen(pname) < 1 || strlen(pname) >25)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter Correctly (Range: 1..25)" ;
			getch() ;
		}
	} while (!valid) ;
	do
	{
		valid = 1;
		gotoxy(5,25) ; clreol() ;
		cout <<"ENTER ADDRESS OF THE PASSENGER" ;
		gotoxy(15,6) ; clreol() ;
		gets(paddress) ;
		if (paddress[0] == '0')
			return ;
		if (strlen(paddress) < 1 || strlen(paddress) >35)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7Enter Correctly (Range: 1..35)" ;
			getch() ;
		}
	} while (!valid) ;
	do
	{
		gotoxy(5,25) ; clreol() ;
		cout <<"ENTER SEX OF THE PASSENGER" ;
		gotoxy(15,7) ; clreol() ;
		psex = getche() ;
		psex = toupper(psex) ;
		if (psex == '0')
			return ;
	} while (psex != 'M' && psex != 'F') ;
	do
	{
		valid = 1 ;
		gotoxy(5,25) ; clreol() ;
		cout <<"ENTER AGE OF THE PASSENGER" ;
		gotoxy(15,8) ; clreol() ;
		gets(t1) ;
		t2 = atoi(t1) ;
		page = t2 ;
		if (t1[0] == '0')
			return ;
		if (page <1 || page >150)
		{
			valid = 0 ;
			gotoxy(5,25) ; clreol() ;
			cout <<"\7ENTER CORRECTLY" ;
			getch() ;
		}
	} while (!valid) ;
	clrscr() ;
	DRAW d ;
	d.BOX(15,5,66,21,'*') ;
	d.LINE_HOR(16,65,7,'*') ;
	gotoxy(33,6) ;
	cout <<"Ticket no. " <<tno ;
	gotoxy(17,9) ;
	cout <<from <<" to " <<to ;
	gotoxy(45,9) ;
	cout <<"Flight no. " <<pfltno ;
	gotoxy(20,11) ;
	cout <<"Passenger Name : " <<pname ;
	gotoxy(20,13) ;
	cout <<"Address : " <<paddress ;
	gotoxy(20,15) ;
	cout <<"Sex : " <<psex ;
	gotoxy(20,17) ;
	cout <<"Age : " <<page ;
	gotoxy(45,19) ;
	if (pclass == 'E')
		cout <<"Total Fair: " <<ecofair ;
	else
		cout <<"Total Fair: " <<exefair ;
	p.ADD_RECORD(tno,sno,pname,paddress,page,psex,pclass) ;
	getch() ;
}

//---------------------------------------------------------------------------
// FUNCTION TO ADD THE GIVEN DATA IN THE PASSENGER'S FILE
//---------------------------------------------------------------------------

void PASSENGER :: ADD_RECORD(int tno, int sno, char pname[26], char paddress[36], int page, char psex, char pclass)
{
	fstream file ;
	file.open("PASS.DAT", ios::app) ;
	ticketno = tno ;
	slno = sno ;
	strcpy(name,pname) ;
	strcpy(address,paddress) ;
	age = page ;
	sex = psex ;
	Class = pclass ;
	file.write((char *) this, sizeof(PASSENGER)) ;
	file.close() ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION RETURN THE LAST TICKETNO. IN THE PASSENGER FILE
//---------------------------------------------------------------------------

int PASSENGER :: LAST_TICKETNO(void)
{
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	int count=0 ;
	while (file.read((char *) this, sizeof(PASSENGER)))
		count = ticketno ;
	file.close() ;
	return count ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION RETURN TOTALNO. OF SEATS IN THE PASSAGER FILE
//---------------------------------------------------------------------------

int PASSENGER :: SEATS(int sno)
{
	fstream file;
	file.open("PASS.DAT", ios::in) ;
	int count = 0 ;
	while (file.read((char *) this, sizeof(PASSENGER)))
	{
		if (sno == slno)
			count++ ;
	}
	file.close() ;
	return count ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION RETURN 0 IF THE TICKET NO. NOT FOUND IN PASSENGER'S FILE
//---------------------------------------------------------------------------

int PASSENGER :: FOUND(int tno)
{
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	int found=0 ;
	while (file.read((char *) this, sizeof(PASSENGER)))
	{
		if (tno == ticketno)
		{
			found = 1 ;
			break ;
		}
	}file.close() ;
	return found ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION RETRNS PASSENGER'S NAME FOR THE GIVEN TICKET NO.
//---------------------------------------------------------------------------

char *PASSENGER :: NAME(int tno)
{
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	while (file.read((char *) this, sizeof (PASSENGER)))
	{
		if (tno == ticketno)
			break ;
	}
	file.close() ;
	return name ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION DISPLAY THE LIST OF THE PASSENGERS
//---------------------------------------------------------------------------

void PASSENGER :: LIST(void)
{
	clrscr() ;
	char t1[10] ;
	int t2, sno, valid ;
	TICKET ticket ;
	ticket.ENQUIRY() ;
	do
	{
		valid = 1 ;
		gotoxy(3,23) ;
		cout <<"				" ;
		gotoxy(3,23) ;
		cout <<"PRESS <ENTER> TO EXIT" ;
		gotoxy(3,20) ;
		cout <<"						" ;
		gotoxy(3,20) ;
		cout<<"Enter Sno. of the FLIGHT for which you want to see list of passenger";
		gets(t1) ;
		t2 = atoi(t1) ;
		sno = t2 ;
		if (strlen(t1) == 0)
			return ;
		if (sno < 1 || sno > 12)
		{
			valid = 0 ;
			gotoxy(3,23) ;
			cout <<"			" ;
			gotoxy(3,23) ;
			cout <<"\7ENTER CORRECTLY" ;
			getch() ;
		}
	} while (!valid) ;
	clrscr() ;
	int row=7, found=0, flag=0 ;
	char ch ;
	DRAW d;
	d.BOX(1,2,80,24,218) ;
	d.LINE_HOR(2,79,4,196) ;
	d.LINE_HOR(2,79,6,196) ;
	d.LINE_HOR(2,79,22,196) ;
	gotoxy(3,3) ;
	cout <<"Flight no. "<<ticket.FLIGHTNO(sno) ;
	gotoxy(32,3) ;
	cout<<"LIST OF PASSENGER" ;
	textcolor(BLACK) ; textbackground(WHITE) ;
	gotoxy(2,5) ;
	cprintf(" TICKET NO.   NAME				CLASS			") ;
	textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	file.seekg(0,ios::beg) ;
	while (file.read((char *) this, sizeof(PASSENGER)))
	{
		if (sno == slno)
		{
			flag = 0 ;
		     //   delay(20) ;
			found =1 ;
			gotoxy(5,row) ;
			cout <<ticketno ;
			gotoxy(17,row) ;
			cout <<name ;
			gotoxy(49,row) ;
			if (Class == 'X')
				cout <<"Executive" ;
			else
				cout <<"Economic" ;
			if ( row == 21 )
			{
				flag = 1 ;
				row = 7 ;
				gotoxy(5,23) ;
				cout <<"Press any key to continue or Press <ESC> to exit";
				ch = getch() ;
				if (ch == 27)
					break ;
				clrscr() ;
				d.BOX(1,2,80,24,218) ;
				d.LINE_HOR(2,79,4,196) ;
				d.LINE_HOR(2,79,6,196) ;
				d.LINE_HOR(2,79,22,196) ;
				gotoxy(2,5) ;
				cprintf(" TICKET NO.	NAME		FLIGHT NO.		CLASS		") ;
				textcolor(LIGHTGRAY) ; textbackground(BLACK) ;
			}
			else
				row++ ;
		}
	}
	if (!found)
	{
		gotoxy(5,10) ;
		cout <<"\7Records not found" ;
	}
	if (!flag)
	{
		gotoxy(5,23) ;
		cout <<"Press any key to continue..." ;
		getch() ;
	}
	file.close() ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION DELETES PASSENGER RECORD FOR THE GIVEN TICKET NO.
//---------------------------------------------------------------------------

void PASSENGER :: DELETE_TICKET(int tno)
{
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	while (!file.eof())
	{
		file.read((char *) this, sizeof(PASSENGER)) ;
		if (file.eof())
			break;
		if (tno != ticketno)
			temp.write((char *) this, sizeof(PASSENGER)) ;
	}
	file.close();
	temp.close() ;
	file.open("PASS.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(PASSENGER)) ;
		if (temp.eof() )
			break ;
		file.write((char *) this, sizeof(PASSENGER)) ;
	}
	file.close() ;
	temp.close() ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION DELETES ALL PASSENGER RECORD FOR THE GIVEN FLIGHT NO.
//---------------------------------------------------------------------------

int PASSENGER :: DELETE_FLIGHT(int sno)
{
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	fstream temp ;
	temp.open("temp.dat", ios::out) ;
	file.seekg(0,ios::beg) ;
	int found = 0 ;
	while (!file.eof())
	{
		file.read((char *) this, sizeof(PASSENGER)) ;
		if (file.eof())
			break;
		if (sno != slno)
			temp.write((char *) this, sizeof(PASSENGER)) ;
		else
			found = 1 ;
	}
	file.close();
	temp.close() ;
	file.open("PASS.DAT", ios::out) ;
	temp.open("temp.dat", ios::in) ;
	temp.seekg(0,ios::beg) ;
	while ( !temp.eof() )
	{
		temp.read((char *) this, sizeof(PASSENGER)) ;
		if (temp.eof() )
			break ;
		file.write((char *) this, sizeof(PASSENGER)) ;
	}
	file.close() ;
	temp.close() ;
	return found ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION CANCELS PASSENGER'S TICKET
//---------------------------------------------------------------------------

void RESERVE :: CANCELLATION(void)
{
	clrscr() ;
	char t1[10], ch ;
	int t2, tno, valid ;
	do
	{
		valid =1 ;
		gotoxy(3,23) ; clreol() ;
		cout <<"PRESS <ENTER> TO SEE LIST or 0 TO EXIT" ;
		gotoxy(3,20) ; clreol() ;
		cout <<"Enter Ticket no. of the Passenger to cancel the Ticket" ;
		gets(t1) ;
		t2 = atoi(t1) ;
		tno = t2 ;
		if (t1[0] == '0')
		{
			valid = 0 ;
			LIST() ;
			clrscr() ;
		}
	} while (!valid) ;
	clrscr() ;
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	while (file.read((char *) this, sizeof(PASSENGER)))
		if (ticketno == tno)
			break ;
	file.close() ;
	int i = 1 ;
	file.open("TICKET.DAT",ios::in) ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if (slno == i)
			break ;
		i++ ;
	}
	file.close() ;
	PASSENGER p;
	DRAW d;
	d.BOX(15,5,66,21,'*') ;
	d.LINE_HOR(16,65,7,'*') ;
	gotoxy(33,6) ;
	cout <<"Ticket no. " <<tno ;
	gotoxy(17,9) ;
	cout <<from <<" to " <<to ;
	gotoxy(45,9) ;
	cout <<"Flight no. "<<fltno ;
	gotoxy(20,11) ;
	cout <<"Passenger Name : " <<p.NAME(tno);
	gotoxy(20,13) ;
	cout <<"Address : " <<address ;
	gotoxy(20,15) ;
	cout <<"Sex : " <<sex ;
	gotoxy(20,17) ;
	cout <<"Age :" <<age ;
	gotoxy(45,19) ;
	if (Class == 'E')
		cout <<"Total Fair: " <<ecofair ;
	else
		cout <<"Total Fair: " <<exefair ;
	do
	{
		gotoxy(10,23) ; clreol() ;
		cout <<"Cancel this ticket (y/n) : " ;
		ch = getche() ;
		ch = toupper(ch) ;
	} while (ch != 'Y' && ch != 'N') ;
	if (ch == 'N')
		return ;
	DELETE_TICKET(tno) ;
	gotoxy(10,25) ;
	cout <<"\7Ticket Cancelled" ;
	getch() ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION DISPLAY THE PASSENGER'S INFORMATION
//---------------------------------------------------------------------------

void RESERVE :: DISPLAY_TICKET(void)
{
	clrscr() ;
	char t1[10], ch ;
	int t2, tno, valid ;
	do
	{
		valid =1 ;
		gotoxy(3,23) ; clreol() ;
		cout <<"PRESS <ENTER> TO SEE LIST or 0 TO EXIT" ;
		gotoxy(3,20) ; clreol() ;
		cout <<"Enter Ticket no. of the Passenger " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		tno = t2 ;
		if (t1[0] == '0')
			return ;
		if (strlen(t1) == 0)
		{
			valid = 0 ;
			LIST() ;
			clrscr() ;
		}
		if (!FOUND(tno) && valid)
		{
			valid = 0;
			gotoxy(3,23) ; clreol() ;
			cout <<"\7Record not found" ;
			getch() ;
		}
	} while (!valid) ;
	clrscr() ;
	fstream file ;
	file.open("PASS.DAT", ios::in) ;
	while (file.read((char *) this, sizeof(PASSENGER)))
		if (ticketno == tno)
			break ;
	file.close() ;
	int i = 1 ;
	file.open("TICKET.DAT",ios::in) ;
	while (file.read((char *) this, sizeof(TICKET)))
	{
		if (slno == i)
			break ;
		i++ ;
	}
	file.close() ;
	PASSENGER p;
	DRAW d;
	d.BOX(15,5,66,21,'*') ;
	d.LINE_HOR(16,65,7,'*') ;
	gotoxy(33,6) ;
	cout <<"Ticket no. " <<tno ;
	gotoxy(17,9) ;
	cout <<from <<" to " <<to ;
	gotoxy(45,9) ;
	cout <<"Flight no. "<<fltno ;
	gotoxy(20,11) ;
	cout <<"Passenger Name : " <<p.NAME(tno);
	gotoxy(20,13) ;
	cout <<"Address : " <<address ;
	gotoxy(20,15) ;
	cout <<"Sex : " <<sex ;
	gotoxy(20,17) ;
	cout <<"Age :" <<age ;
	gotoxy(45,19) ;
	if (Class == 'E')
		cout <<"Total Fair: " <<ecofair ;
	else
		cout <<"Total Fair: " <<exefair ;
	gotoxy(10,25) ;
	cout <<"Press any Key to continue..." ;
	getch() ;
}

//---------------------------------------------------------------------------
// THIS FUNCTION GIVE FLIGHT NO. TO DELETE ALL PASANGER RECORDS
//---------------------------------------------------------------------------

void RESERVE :: DELETE_ALL(void)
{
	clrscr() ;
	ENQUIRY() ;
	char t1[5] ;
	int t2, valid, sno ;
	do
	{
		valid = 1 ;
		gotoxy(3,23) ;
		cout <<"				" ;
		gotoxy(3,20) ;
		cout <<"						" ;
		gotoxy(3,20) ;
		cout <<"Enter Sno. of the FLIGHT for which all passenger records to be deleted : " ;
		gets(t1) ;
		t2 = atoi(t1) ;
		sno = t2 ;
		if (strlen(t1) == 0)
			return ;
		if (sno < 1 || sno > 12)
		{
			valid = 0 ;
			gotoxy(3,23) ;
			cout <<"			" ;
			gotoxy(3,23) ;
			cout <<"\7ENTER CORRECTLY" ;
			getch() ;
		}
	} while (!valid) ;
	gotoxy(3,23) ;
	if (!DELETE_FLIGHT(sno))
		cout <<"\7Records not found. Press any key to continue..." ;
	else
		cout <<"\7Records deleted. Press any key to continue..." ;
	getch() ;
}

//---------------------------------------------------------------------------
// THIS IS MAIN FUNCTION WHICH DISPLAY MENU AND CALLS ALL THE MAIN FUNCTION
//---------------------------------------------------------------------------

void main(void)
{
	DRAW d ;
	PASSENGER p ;
	TICKET ticket ;
	RESERVE r ;
	ticket.ADDITION() ;
	char ch ;
	while (1)
	{
		clrscr() ;
		d.BOX(19,6,62,20,218) ;
		textcolor(BLACK) ;
		textbackground(WHITE) ;
		for (int i=7; i<=19; i++)
			for (int j=20; j<=61; j++)
			{
				gotoxy(j,i) ;
				cprintf(" ") ;
			}
		gotoxy(29,9) ;
		cprintf("AIR TICKET RESERVATION") ;
		gotoxy(29,10) ;
		cprintf("~~~~~~~~~~~~~~~~~~~~~~") ;
		gotoxy(30,11) ;
		cprintf("1 : RESERVATION") ;
		gotoxy(30,12) ;
		cprintf("2 : CANCELLATION") ;
		gotoxy(30,13) ;
		cprintf("3 : PASSENGER RECORDS ->") ;
		gotoxy(30,14) ;
		cprintf("4 : ENQUIRY") ;
		gotoxy(30,15) ;
		cprintf("5 : LIST OF PASSENGERS") ;
		gotoxy(30,16) ;
		cprintf("6 : QUIT") ;
		gotoxy(30,18) ;
		cprintf("ENTER YOUR CHOICE ") ;
		ch = getche() ;
		textcolor(LIGHTGRAY) ;
		textbackground(BLACK) ;
		clrscr() ;
		if (ch == 27 || ch == '6')
			break ;
		else
		if (ch == '1')
			r.RESERVATION() ;
		if (ch == '2')
			r.CANCELLATION() ;
		if (ch == '4')
		{
			ticket.ENQUIRY() ;
			gotoxy(2,23) ;
			cout <<"Press any key to continue..." ;
			getch() ;
		}
		else
		if (ch == '5')
			p.LIST() ;
		else
		if (ch == '3')
		{
			while(1)
			{
			clrscr() ;
			d.BOX(19,6,62,20,218) ;
			textcolor(BLACK) ;
			textbackground(WHITE) ;
			for (int i=7; i<=19; i++)
				for (int j=20; j<=61; j++)
				{
					gotoxy(j,i) ;
					cprintf(" ") ;
				}
			gotoxy(29,10) ;
			cprintf("EDIT PASSENGER RECORD") ;
			gotoxy(29,11) ;
			cprintf("~~~~~~~~~~~~~~~~~~~~~") ;
			gotoxy(33,12) ;
			cprintf("1 : PASSENGER INFORMATION") ;
			gotoxy(33,13) ;
			cprintf("2 : DELETE") ;
			gotoxy(33,14) ;
			cprintf("0 : EXIT") ;
			gotoxy(31,16) ;
			cprintf("ENTER YOUR CHOICE") ;
			ch = getche() ;
			textcolor(LIGHTGRAY) ;
			textbackground(BLACK) ;
			clrscr() ;
			if (ch == 27 || ch == '0')
				break ;
			else
			if (ch == '1')
				r.DISPLAY_TICKET();
			else
			if (ch == '2')
				r.DELETE_ALL() ;
			}
		}
	}
}
