#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <vector>

#include <algorithm>
#include <functional>

#include <time.h>

using namespace std;

//#define NUM_ROWS 14

void DrawFirstData();

struct SForFile
{
	char Familiya[100];
	char Name[100];
	char Date[11];
	char Telefon[30];
};

unsigned long parsedate(string sdate)
{
	char d[3];
	char m[3];
	char y[5];
	memset(d,0,3);
	memset(m,0,3);
	memset(y,0,5);
	char * link = (char *)sdate.c_str();
	int i,j,l;
	i=0;
	j=0;
	l=sdate.size();
	while (link[j]!='.'&&j<l&&i<2){d[i]=link[j];j++;i++;}
	if (link[j]=='.')j++;
	i=0;
    while (link[j]!='.'&&j<l&&i<2){m[i]=link[j];j++;i++;}
	if (link[j]=='.')j++;
	i=0;
    while (j<l&&i<4){y[i]=link[j];j++;i++;}
	return atoi(y)*10000+atoi(m)*100+atoi(d);
}

class Person{
public:
Person(){}
~Person(){}

string GetFamiliya(){ return persFamiliya;}
string GetName(){ return persName;}
string GetData(){ return persData;}
string GetTelefon(){ return persTelefon;}

void SetFamiliya(string fam){ persFamiliya=fam;}
void SetName(string name){ persName=name;}
void SetData(string data){ persData=data;}
void SetTelefon(string tel){ persTelefon=tel;}

void Print();

 void toFileS(SForFile *sf);
 void fromFileS(SForFile *sf);

bool operator<(Person a)
{
	bool ret=false;	
	switch(Person::cmpfield)
	{
	case 0:
		//if (persFamiliya<a.persFamiliya) cout<<"t";else cout<<"f";
		return persFamiliya<a.persFamiliya;
	case 1:
		return persName<a.persName;
	case 2:
		return parsedate(persData)<parsedate(a.persData);
	case 3:
		return persTelefon<a.persTelefon;
	case 4:
		return (persFamiliya<a.persFamiliya)&&
			   (persName<a.persName) &&
			   (persData<a.persData) &&
			   (persTelefon<a.persTelefon);
	}
	return ret;
}

bool operator>(Person a)
{
	bool ret=false;
	switch(Person::cmpfield)
	{
	case 0:
		return persFamiliya>a.persFamiliya;
	case 1:
		return persName>a.persName;
	case 2:
		return persData>a.persData;
	case 3:
		return persTelefon>a.persTelefon;
	case 4:
		return (persFamiliya>a.persFamiliya)&&
			   (persName>a.persName) &&
			   (persData>a.persData) &&
			   (persTelefon>a.persTelefon);
	}
	return ret;
}

bool operator==(Person a)
{
	bool ret=false;
	switch(Person::cmpfield)
	{
	case 0:
		return persFamiliya==a.persFamiliya;
	case 1:
		return persName==a.persName;
	case 2:
		return persData==a.persData;
	case 3:
		return persTelefon==a.persTelefon;
	case 4:
		return (persFamiliya==a.persFamiliya)&&
			   (persName==a.persName) &&
			   (persData==a.persData) &&
			   (persTelefon==a.persTelefon);
	}
	return ret;
}

static void Person::setCmpF(int cf){cmpfield=cf;}
static int Person::getCmpF(){return cmpfield;} 

private:
string persFamiliya;
string persName;
string persData;
string persTelefon;
static int cmpfield;
};

int Person::cmpfield;

void Person::toFileS(SForFile *sf)
{	
	size_t size= persFamiliya.size();
	if (size>99)size=99;
	memcpy((void *)sf->Familiya,(void *)persFamiliya.c_str(),size+1);	
	size=persName.size();
	if (size>99)size=99;
    memcpy((void *)sf->Name,(void *)persName.c_str(),size+1);
	size=persData.size();
	if (size>10)size=10;
	memcpy((void *)sf->Date,(void *)persData.c_str(),size+1);
	size=persTelefon.size();
	if (size>29)size=29;
	memcpy((void *)sf->Telefon,(void *)persTelefon.c_str(),size+1);
}

void Person::fromFileS(SForFile *sf)
{
 persFamiliya = sf->Familiya;
 persName = sf->Name;
 persData = sf->Date;
 persTelefon = sf->Telefon;
}

vector <Person> pers;

class Rus {
public:
Rus(const char* text): data(new char [strlen( text)+1]) {CharToOemA( text, data);}
~Rus() {delete [] data;};
operator const char* () const {return data;}

private:
char* data;
};


void Person::Print()
{	
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute ( H, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY );
  printf("| %-20.20s| %-12.12s| %-12.12s| %-12.12s|\n",persFamiliya.c_str(),persName.c_str(),persData.c_str(),persTelefon.c_str());
}

void PrintMenu()
{


        cout<<endl;
               std::cout <<Rus("Выбирите действие")<<std::endl;
              std::cout <<Rus("1 - Вывести книгу")<<std::endl;
               std::cout <<Rus("2 - Сортировка")<<std::endl;
               std::cout <<Rus("3 - Поиск")<<std::endl;
               std::cout <<Rus("4 - Добавить")<<std::endl;
               std::cout <<Rus("5 - Удалить")<<std::endl;
			   std::cout <<Rus("6 - Выход")<<std::endl;
   			  

std::cout <<"-------------------------------------------------" << std::endl;
}

void PrintAll()
{
system("cls");
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute ( H, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY );

        //cout<<Rus("***---------  Записная книжка  --------------***\n");	
	cout<<Rus("                    ТЕЛЕФОННАЯ КНИГА")<<std::endl;
	cout<<"----------------------------------------------------------------"<<endl;
cout<<Rus("|    Фамилия          | Имя         |Дата рождения|  Tелефон    | ")<<std::endl;
	cout<<"----------------------------------------------------------------"<<endl;
	cout<<"|                     |             |             |             | "<<endl;


for(unsigned int n=0; n<pers.size(); n++)
{
pers[n].Print();
}

cout<<"-----------------------------------------------------------------\n";
}


int GetNumber(int imin, int imax){
 int number=imin-1;
 while(true)
 {
   cin >> number;
   if((number>=imin) && (number <=imax)) break;
   else
   {
        cout <<Rus( "Повторите ввод" )<< endl;
		cin.clear();
        while(cin.get()!='\n'){}
   }
 }
 return number;
}

void SortPerson_p(int field)
{
	Person::setCmpF(field);
	sort(pers.begin(),pers.end());
}

void PrintPage(int pagenum)
{
	system("cls");
DrawFirstData();

        
cout<<Rus("                    ТЕЛЕФОННАЯ КНИГА  страница: ")<<pagenum+1<<std::endl;
	cout<<"----------------------------------------------------------------"<<endl;
cout<<Rus("|    Фамилия          | Имя         |Дата рождения|  Tелефон    | ")<<std::endl;
	cout<<"----------------------------------------------------------------"<<endl;
	cout<<"|                     |             |             |             | "<<endl;

unsigned int endh = pagenum*10+10;
if (endh>pers.size())endh=pers.size();
for(unsigned int n=(pagenum*10); n<endh; n++)
{
pers[n].Print();
}

cout<<"-----------------------------------------------------------------\n";
cout<<Rus("ESC - выход  1 - сортировка по фамилии 2 - по имени 3 - по дате 4 - по телефону PgUp - вверх PgDn - вниз")<<endl;
}

void PrintAll2()
{
	unsigned int s = pers.size()/10+1;
    bool stop=false;
	int curpage = 0;
	

	while(!stop)
	{     
	 PrintPage(curpage);	 
     int cmd= getch();
	 if (cmd==224){cmd=getch()+1000;}	 
	 switch(cmd)
	 {
	 case 49:
		    SortPerson_p(0);curpage=0;
		    break;
	 case 50:
		    SortPerson_p(1);curpage=0;
		    break;
	 case 51:
		    SortPerson_p(2);curpage=0;
		    break;
	 case 52:
		    SortPerson_p(3);curpage=0;
		    break;
	 case 1073:
		    curpage--;if (curpage<0)curpage=0;
		    break;
	 case 1081:
		    curpage++;if(curpage>s)curpage=s;
		   break;
	 case 27:
		   system("cls");
		   stop=true;
		   break;
	 }
	}
}

void SortPerson()
{
  system("cls");
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute ( H, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY );

  cout<<Rus("***----------  сортировка  ---------------***\n");
  cout<<Rus("Введите параметр\n");
  cout<<Rus(" 1 - Фамилия\n");
  cout<<Rus(" 2 - Имя\n");
  cout<<Rus(" 3 - Телефон\n");
  cout<<Rus(" 4 - Выход\n");

  int vybor=GetNumber(1,4);

  if (vybor<4){
	
   switch(vybor)
   {
   case 1:
	    Person::setCmpF(0);		
	    break;
   case 2:
	    Person::setCmpF(1);		
	    break;
   case 3:
	    Person::setCmpF(3);		
	    break;  
   case 4:
	      system("cls");
		  break;
   } 
   sort(pers.begin(),pers.end()); 
   PrintAll();
  }
}




int tolower_rus(int ch)
{
	string alf = Rus("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЪЭЮЯ");
	string alfl = Rus("абвгдеёжзийклмнопрстуфхцчшщьыъэюя");

	int pos = -1;
	for (int i=0;i<alf.size();i++)
	{if (alf[i]==ch){pos=i;break;}}	
	if (pos==-1)return ch;
	return alfl[pos];
}

bool Match(string expr2,string val2)
{
	string expr = expr2;
	string val = val2;
	int i,j,k,g;//указатели в строках
	int ml,mv;//длины строк
	int stat =0;//состояние автомата
	bool s;
    
	for (i=0;i<expr.size();i++)
	{expr[i] = tolower_rus(expr[i]);
	 expr[i] = tolower(expr[i]);
	}
	for (i=0;i<val.size();i++)
	{   val[i] = tolower_rus(val[i]);
		val[i] = tolower(val[i]);
	}

    i=0;
	j=0;
	ml=expr2.size();
	mv=val2.size();
	while(j<mv&&i<ml)
	{
	 switch(expr[i])
	 {
	 case '*'://несколько или ни одного
		 if (i+1<ml)
		 {
           k=i+1;
		   if (expr[k]==val[j]||expr[k]=='?')
		   {//здесь надо попытаться пройти по шаблону либо  до следующей звёздочки или ? либо до конца
              g=j;
			  s=true;
			  while(g<mv&&k<ml&&s)
			  {
				  switch(expr[k])
				  {
				  case '*':
					    j=g;i=k;
						s=false;
					  break;
				  case '?':
					    g++;k++;
					  break;
				  default:
					  if (expr[k]==val[g]){g++;k++;}
					  else 
					  {
						  j++;//добавляем одну букву к пройденому и пытаемся опять сверить строки
						  s=false;
					  }
				  }				  
			  }
			  if (k>=ml&&g>=mv)return true;              
			  if (k<ml&&g>=mv) return false;
			  if (s&&g<mv&&k>=ml)j++;			  
		   }
		   else		   
			   j++;		   
		 }
		 else
			 return true;//звёздочка на конце выражения дальше можно не смотреть
         break;
	 case '?'://один пропускаем
		 i++;j++;break;
	 default: // просто символ
		 if (expr[i]==val[j]){i++;j++;}
		 else {return false;}//посимвольное не совпадение
	 }	 
	}
	if (j<mv)return false;//выражение закончилось раньше чем строка
	if (i<ml)return false;//строка закончилась раньше чем выражение
	return true;
}

void FindPerson()
{
  system("cls");
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute ( H, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY );
 
  cout<<Rus("--------------------- поиск записи -------------------------\n");
  cout<<Rus("Выбирите критерий поиска\n");
  cout<<Rus(" 1 - Фамилия\n");
  cout<<Rus(" 2 - Имя\n");
  cout<<Rus(" 3 - Дата рождения\n");
  cout<<Rus(" 4 - Телефон\n");
  cout<<Rus(" 5 - Выход\n");
  int vybor=GetNumber(1,5);

  if (vybor<5)
  {
	  string key;
	  string vkey;
	  bool found = false;
	  switch(vybor)
	  {
	  case 1: cout<<Rus("Введите фамилию: ");break;
	  case 2: cout<<Rus("Введите имя: "); break;
	  case 3: cout<<Rus("Введите дату рождения: ");break;
	  case 4: cout<<Rus("Введите телефон: ");break;
      case 5:
	          system("cls");
		      break;
	  }
	  cin>>key;

         cout<<"----------------------------------------------------------------"<<endl;
         cout<<Rus("|    Фамилия          | Имя         |Дата рождения|  Tелефон    | ")<<std::endl;
	     cout<<"----------------------------------------------------------------"<<endl;
	     cout<<"|                     |             |             |             | "<<endl;
	  unsigned int n=0;
      while (n<pers.size())
	  {	
         switch(vybor)
		 {
		 case 1:vkey=pers[n].GetFamiliya();break;
		 case 2:vkey=pers[n].GetName();break;
		 case 3:vkey=pers[n].GetData();break;
		 case 4:vkey=pers[n].GetTelefon();break;
		 }
         if (Match(key,vkey))
		 {
          found=true;
		  pers[n].Print();		           
		 }
		 n++;
	  }
	  cout<<"----------------------------------------------------------------"<<endl;
	  if (!found)	 	  
		  cout<<Rus("Нет такой записи\n");

  }
}



void AddPerson(){system("cls");
HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute ( H, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE| BACKGROUND_INTENSITY );

string sbuf;
Person bufPers;
cout<<endl;

                cout<<Rus("----------------  Добавление записи ----------------\n");
cout<<Rus("Фамилия: ");
cin>>sbuf;
bufPers.SetFamiliya(sbuf);

cout<<endl;
cout<<Rus("Имя: ");
cin>>sbuf;
bufPers.SetName(sbuf);

cout<<endl;
cout<<Rus("Дата рождения: ");
cin>>sbuf;
bufPers.SetData(sbuf);

cout<<endl;
cout<<Rus("Телефон:");
cin>>sbuf;
bufPers.SetTelefon(sbuf);

pers.push_back(bufPers);
cout<<"----------------------------------------------------------------"<<endl;
}


void DeletePerson(){
 string sbuf;
 unsigned int n=0;
 bool find=false;

 system("cls");


 cout<<Rus("----------------  Удаление записи ---------------\n");
 cout<<Rus("Выбирите критерий выбора записей на удаление\n");
  cout<<Rus(" 1 - Фамилия\n");
  cout<<Rus(" 2 - Имя\n");
  cout<<Rus(" 3 - Дата рождения\n");
  cout<<Rus(" 4 - Телефон\n");
  cout<<Rus(" 5 - Выход\n");
  int vybor=GetNumber(1,5);

  if (vybor<5)
  {
	  string key;
	  string vkey;
	  bool found = false;
	  switch(vybor)
	  {
	  case 1: cout<<Rus("Введите фамилию: ");break;
	  case 2: cout<<Rus("Введите имя: "); break;
	  case 3: cout<<Rus("Введите дату рождения: ");break;
	  case 4: cout<<Rus("Введите телефон: ");break;
	  case 5:
	      system("cls");
		  break;
	  }
	  cin>>key;
	     cout<<Rus("Удалены следующие записи:")<<endl;
         cout<<"----------------------------------------------------------------"<<endl;
         cout<<Rus("|    Фамилия          | Имя         |Дата рождения|  Tелефон    | ")<<std::endl;
	     cout<<"----------------------------------------------------------------"<<endl;
	     cout<<"|                     |             |             |             | "<<endl;
	  unsigned int n=0;
      while (n<pers.size())
	  {	
         switch(vybor)
		 {
		 case 1:vkey=pers[n].GetFamiliya();break;
		 case 2:vkey=pers[n].GetName();break;
		 case 3:vkey=pers[n].GetData();break;
		 case 4:vkey=pers[n].GetTelefon();break;
		 }
         if (Match(key,vkey))
		 {
          found=true;
		  pers[n].Print();
		  pers.erase(pers.begin()+n);		  		 
		 }
		 else
		 n++;
	  }
	  cout<<"----------------------------------------------------------------"<<endl;
	  if (!found)	 	  
		  cout<<Rus("Не найдено ни одной записи\n");

  }

}








void DrawFirstData()
{
	tm *curtime;
	time_t mtime;

	time(&mtime);
	curtime=localtime(&mtime);
    long mytime = (curtime->tm_year+1900)*10000+
		(curtime->tm_mon+1)*100+curtime->tm_mday;
	mytime = mytime%10000;// год не учитывать
	cout<<Rus("Текущая дата: ")<<curtime->tm_mday<<"."<<curtime->tm_mon+1<<"."<<curtime->tm_year+1900<<endl;
    long mindelta = 10000;	
	Person adds;
	
    long pdate = 0;

	
	for (unsigned int i=0;i<pers.size();i++)
	{
		pdate = (long)parsedate(pers[i].GetData());
		pdate = pdate%10000;//год не учитывать
		if ( (pdate-mytime)>0&&(pdate-mytime)<mindelta)
		{
			mindelta = pdate-mytime;
            adds = pers[i];
		}
	}

	if (mindelta!=10000)
	{
	 cout<<Rus("Ближайший день рождения у ")<<endl;
	  
	 for (unsigned int i=0;i<pers.size();i++)
	{
		pdate = (long)parsedate(pers[i].GetData());
		pdate = pdate%10000;//год не учитывать
		if ( (pdate-mytime)>0&&(pdate-mytime)==mindelta)
		{			         
			cout<<pers[i].GetFamiliya()<<"\t"<<pers[i].GetName()<<"\t"<<pers[i].GetData()<<"\t"<<pers[i].GetTelefon()<<endl;
		
		}
	}
	 
	}
}
