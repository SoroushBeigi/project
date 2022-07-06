#include<bits/stdc++.h>
using namespace std ;
//------------------------------------------------
//prototypes

string char_to_str(char []);
bool in(char , string);
class ArticleList;
float dot_product(vector<int>,vector<int>);

//------------------------------------------------
//classes

class Account 
{
	 
	private :
	 string Username , Password ;
	  
	public :
		Account(string user ,string pass) : Username(user) , Password(pass) {}
		Account(){}
		void p()//temporary method to show values of calsses , dude !!
		{
			cout<<Username<<endl;
			cout<<Password<<endl;
		}

		int RatePassword()
		{
			int len , upper=0 ,lower=0 , sign=0 ; 
			len = Password.length();
			for(int i = 0 ; i<len ; i++)
			{
				if(Password[i]>=65 && Password[i]<=90) upper ++;
				else if(Password[i]>=97 && Password[i]<=122)lower ++;
				else sign ++ ;
			}
			// security 
			if(len<=10)
			{
				if((upper==0 && lower==0) ||(upper==0 && sign==0) || (sign==0 && lower==0)) return 0 ;
				if(upper==0 || lower==0 ||sign==0) return 1 ;
				if(upper>=3 && lower>=3 &&sign>=3) return 5 ;
				if(upper>=2 && lower>=2 &&sign>=2) return 4 ;
				return 3 ;
				
			}
			else if(len<=20)
			{
				if((upper==0 && lower==0) ||(upper==0 && sign==0) || (sign==0 && lower==0)) return 2 ;
				if(upper==0 || lower==0 ||sign==0) return 3 ;
				if(upper>=6 && lower>=6 &&sign>=6) return 7 ;
				if(upper>=4 && lower>=4 &&sign>=4) return 6 ;
				if(upper>=2 && lower>=2 &&sign>=2) return 5 ;
				return 4 ;
			}
			else 
			{
				if((upper==0 && lower==0) ||(upper==0 && sign==0) || (sign==0 && lower==0)) return 3 ;
				if(upper==0 || lower==0 ||sign==0) return 5 ;
				if(upper>=12 && lower>=12 &&sign>=12) return 10 ;
				if(upper>=10 && lower>=10 &&sign>=10) return 9 ;
				if(upper>=6 && lower>=6 &&sign>=6) return 8 ;
				if(upper>=4 && lower>=4 &&sign>=4) return 7 ;
				if(upper>=2 && lower>=2 &&sign>=2) return 6 ;
				return 5 ;
			}
		}
	    void suggested_password()
	    {
			srand(time(0));
			string str = "0987654321!@#$%^&*<>abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
			int x = rand()%31+ 15;
			string strong_pass ="";
			for(int i= 0 ; i<= x ; i++)
			{
				int j = rand()%72 ;
				strong_pass +=  str[j];
			}
			Password = strong_pass;
			cout<<"your new password is : "<<endl;
			cout<<Password<<endl;	
	    }
		
		friend class AccountList;
	
};

class Article 
{
	friend float s(Article , Article);
	
    protected:
    bool situation;
    vector<string>words;
    vector<string> Article_Name ;
    int people_count;
	string  ID , Ref_ID , Date ;
	vector<Account> accounts;
	
	string Name , text;
	
	public :
		Article(string name ,string id , string ref_id , string date, string txt,int people)
		{
			Name = name ; ID = id ; Ref_ID = ref_id ; Date = date ;
            people_count=people;
			text = txt;
			
		}
		Article(){}
    void add_account(Account acc)
	{
        accounts.push_back(acc);
    }   
    void text_split(vector <string> s)
    {
    	for(int i=0 ; i<s.size() ;i++)
    	{
    		words.push_back(s[i]);
		}
	}
	void name_split(vector<string>s)
	{
		for(int i=0 ; i<s.size();i++)
		{
			Article_Name.push_back(s[i]);
		}
	}
	void set_situation()
	{
		situation = false;
	}
	bool paran_check ()//prantezo check minkw
	{
		int c = 0;
		for(int i=0 ;i<text.length() ;i++)
		{
			if(text[i]==')')c--;
			if(c<0) return false;
			else if(text[i] ='(')c++;
		}
		if(c!=0)return false;
		return true;
	}
	bool syntax_check() // check syntax of article
	{
		if(!in(text[1],"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") )
		{
			cout<<"the first letter must be capital : "<<text[1]<<endl;
			return false;
		}
		if(text[text.length()-1]!='.')
		{
			cout<<"akharesh noghte nazashti !! "<<text[text.length()-1] <<endl;
		}
		
		for(int i=2;i<text.length()-1; i++)
		{
			if(text[i]=='\n')
			{
				if(text[i-1]!='.')
				{ cout<<"noghte sar khat nazashti !? "<<endl; return false ;}
				else 
				{
					if(!in(text[i+1],"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"))
					{
						cout<<"the first letter of each line must be capital !!?"<<endl;
						return false;
					}
				}
			}
			if(text[i]=='.')
			{
				if(text[i+1]!='\n')
				{
					if(!in(text[i+1],"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"))
					{
						cout<<"the first letter of each line must be capital !!?"<<endl;
						return false;
					}
				}
			}
			if(in(text[i],".,?!:()"))
			{
				if(in(text[i-1],".,?!:()") || in(text[i+1],".,?!:()"))
				{
					cout<<"alaem negareshi kenar ham bekar raftan :> !!"<<endl;
					return false;
				}
			}
			if(in(text[i],".,?!:()"))
			{
				if(!in(text[i-1] , "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"))
				{
					cout<<"ghabl az negareshi hrouf & adad bayad biyad"<<endl;
					return false;
				}
				if(in(text[i+1] , "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"))
				{
					cout<<"space bad az alaem negareshi nazashti !!"<<endl;
					return false ;
				}
			}
			
		}
		return  true ;
	}
	bool para_checK()//check teh num of paragraphs
	{
		int p = 0;
		for(int i=0 ; i<text.length() ; i++)
		{
			if(text[i]=='\n') p++;
		}
		if(p >=2)return true;
		cout<<"kamtar az do paragraphe "<<endl;
		return false ;
	}
	bool words_check() // check 100<num of words<5000
	{
		if(words.size()<=5000 && words.size() >=10) return true ;           //baraye rahati dah gozashtam
		cout<<"less than 10!"<<endl;
        return false;
	}
	bool name_check() // check words of name count <=12
	{
		if(Name.length()<=12||Name.length()>0) return true;
		cout<<"name above 12 "<<endl;
		return false;
	}
	bool fifty_check()// check if there is a word with above 50 reptitions //emtiazi
	{
		for(int i=0 ; i<words.size() ; i++)
		{
			int c = 0; c= count(words.begin() , words.end() , words[i]);
			if (c>2) 
			{
				cout<<"kalame << "<<words[i]<<" >> bish az 50 bar tekrar shode !"<<endl;
				return false;
			}
		}
		return true;
	}

	
	string get_id()
	{
		return ID;
	}
	string get_ref_id()
	{
		return Ref_ID;
	}
	string get_name()
	{
		return Name;
	}

	friend class ArticleList; 
	friend class Validate;


};


class AccountList
{
	static int num_accounts ;
	vector<Account>total_accounts;
	
	public:
		void add_Account(Account acc)
		{
			total_accounts.push_back(acc);
			num_accounts++;
		}
		bool created_account(string user , string pass)
		{
			for(int i=0; i<total_accounts.size() ; i++)
			{
				if(total_accounts[i].Username == user && total_accounts[i].Password == pass )
				return true;
			}
			return false;
		}
	
};
class ArticleList
{
	static int num_articles;
	vector<Article>total_articles;
	
	public:
		ArticleList()
		{
			total_articles.clear();
		}
		void add_Article(Article art)
		{
			total_articles.push_back(art);
			num_articles++;
		}
		
		void ppp()
	   {
			for(int i=0 ; i<total_articles.size() ; i++)
			{
				for(int j=0 ; j<total_articles[i].Article_Name.size(); j++) cout<<total_articles[i].Article_Name[j]<<":";
				for(int z =0 ; z<total_articles[i].words.size(); z++) cout<<total_articles[i].words[z]<<"&";
				cout<<endl;
			}
		
		}
		bool article_check(string id)
		{
			for(int i=0 ;i<num_articles ; i++)
			{
				if(total_articles[i].get_id() == id)
				return true;
			}
			return false;
		}
		Article get_Art(string id)
		{
			for(int i=0 ;i<num_articles ; i++)
			{
				if(total_articles[i].get_id ()== id)
				return total_articles[i];
			}
		}
		int get_num()
		{
			return num_articles;
		}
      
	    friend class Article;

	
};


//------------------------------------------------
//functions

int count_element(string str , vector<string>v)
{
	int c =0; 
	for(int i=0 ;i<v.size();i++)
	{
		if(v[i]==str)c++;
	}
	return c;
}

bool in_vector(string str,vector<string>v)
{
	for(int i=0 ;i<v.size() ;i++)
	{
		if(str == v[i])return true;
	}
	return false;
}


float magnitude(vector<int>a)
{
	float result =0;
	for(int i=0 ; i<a.size() ; i++)
	{
		result += a[i]*a[i];
	}
	result = pow(result,0.5);
	return result;
}
float dot_product(vector<int>a,vector<int>b)
{
	float result = 0;
	for(int i=0 ; i<a.size() ;i++)
	    result += a[i]*b[i];
	return result;
}
float s(Article a , Article b)//similarity percent;
{
	float sim_percent=0;
    vector<string> common;
    for(int i=0 ; i<a.words.size(); i++)
    {
    	
    	for(int j = 0 ; j<b.words.size();j++)
    	{
    		if(a.words[i]==b.words[j]&& !in_vector(a.words[i],common)) {
			common.push_back(a.words[i]);
    		break;}
		}
		
	}
	vector<int>v1;
	for(int i=0 ;i<common.size();i++)
	{
	        int c = 0;

			c = count_element(common[i],a.words);
			v1.push_back(c);
	}

	
    vector<int>v2;
    for(int i=0 ;i<common.size();i++)
	{int c = 0;
			c = count_element(common[i],b.words);
			v2.push_back(c);
	}
	
		sim_percent = dot_product(v1,v2)/(magnitude(v1)*magnitude(v2));
	return sim_percent*100;
	


}



bool in(char ch , string s) // like << in >> in python
{
	//string s= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	for(int i=0 ;i<s.length();i++)
	{

		if(s[i]==ch)return true;
	}
	return false;
	
}
vector<string> split(string str) //split string
{
	str +=".";
	vector<string>vec;
	string temp="";
	for(int i=0 ; i<str.length();i++)
	{
		if(in(str[i],"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789") )
		{
			temp+=str[i];
		}
		else
		{
			if(temp!="")
			    vec.push_back(temp);
			temp ="";
		}
		
	}
	return vec;
}
string char_to_str(char []);

//--------------------------------------
//static values
int ArticleList :: num_articles = 0;
int AccountList :: num_accounts =0;



int main()
{
	AccountList AccList;
	ArticleList ArtList;

	char sit ; cout<<" start -> enter s : "; cin>>sit;
	while(sit == 's')
	{
		int order;;
		cout<<"\n"<<"choose your operations (hint -> enter 0) : ";
        cin>>order;
    
       switch (order){

       case -1: exit(0); break; // EXIT 
		case  0 : // hint
			{
				cout<<"\n"<<"-1 : exit";
				cout<<"\n"<<" 0 : hint";
				cout<<"\n"<<" 1 : create account";
				cout<<"\n"<<" 2 : create article";
				cout<<"\n"<<" 3 : article validation";
				cout<<"\n";

				break;
			}

       case 1: 
	   {   
	        //create account
	        string ans ;
       		cout<<"Enter your Username: "<<endl;
       		string user,pass;
       		cin>>user;
       		cout<<"Enter your Password: "<<endl;
       		cin>>pass;
       		Account acc(user , pass);
       		if(AccList.created_account(user,pass))
       		{
       			cout<<"the account exists !?"<<endl;break;
			}
			else
			{
				cout<<"your password security is (1-10) :  "<<acc.RatePassword()<<endl;
       			if(acc.RatePassword()<=7)
			   	{
			   	
       				cout<<endl<<"do you want a strong pass ? (y/n) : ";
       				cin>>ans;
       				if(ans=="y")
       				{
       					acc.suggested_password();
					}
			   	}
			   	AccList.add_Account(acc);
       
			}      
		     break;
        }
       case 2:{
            //create article
           
           int n = 1 ;
           string id,ref_id,date , spoil;
           string name , txt;
           char text[40000];
           cin.ignore(100, '\n');
           cout<<"Enter Article's name: "<<endl;
           getline(cin , name);
           cout<<"Enter Article's ID: "<<endl;
           cin>>id;
           cout<<"Enter Article's reference ID: "<<endl;
           cin>>ref_id;
           cout<<"Enter Article's Date: "<<endl;
           cin>>date;
           cout<<"Enter Article's Text and add a '$' char in the end: "<<endl;
           cin.get(text,sizeof(text),'$');cin>>spoil;
           txt=char_to_str(text);//char to str
           cout<<"Enter participating people count: "<<endl;
           cin>>n;
           Article article(name,id,ref_id,date,txt,n);
           while(n>10 || n<=0){
               cout<<"Error: Enter a number between 1 and 10"<<endl;
               cin>>n;
           }
           for(int i=0; i<n ;i++){
               string user,pass , ans;
               cout<<"Enter Person Number "<<(i+1)<<"'s Username: "<<endl;
               cin>>user;
               cout<<"Enter Person Number "<<(i+1)<<"'s Password: "<<endl;
               cin>>pass;
               Account acc(user,pass);
               if(AccList.created_account(user,pass))
               {
               	    cout<<"your account exists !!"<<endl;
               	    article.add_account(acc);
			   }

			   else
			   {
			   		cout<<"your password security is (1-10) :  "<<acc.RatePassword()<<endl;
       		        if(acc.RatePassword()<=7)
			   			cout<<endl<<"do you want a strong pass ? (y/n) : ";
       			    cin>>ans;
       			    if(ans=="y")
       				{
       					acc.suggested_password();
					}
					cout<<"your account was created successfully !!"<<endl;
					article.add_account(acc);
				
			   }
			   


           }
           article.name_split(split(name));
           article.text_split(split(txt));
           ArtList.add_Article(article);

           

           break;
       }

       
       case 3:
       	{
       		string id; 
       		cout<<"enter the id of article"<<endl;
       		cin>>id;
       		
       	    if(	!ArtList.article_check(id))
       	    {
       	    	cout<<"id doesn't exist !!"<<endl;
       	    	break;
			}
			cout<<"please wait!!"<<endl<<endl;
			Article art;
			art = ArtList.get_Art(id);

			if(art.para_checK()||art. words_check()||
			   art.fifty_check()||art.name_check ()||art.fifty_check())
			   {
			   	 cout<<"the article rejected"<<endl;
			   }

			break;
		}
       case 4:
       	{
       		string id1 , id2; 
       		cout<<"enter the id of 1st article"<<endl;
       		cin>>id1;
       		
       	    if(	!ArtList.article_check(id1))
       	    {
       	    	cout<<"id doesn't exist !!"<<endl;
       	    	break;
			}
			cout<<"enter the id of 2nd article"<<endl;
       		cin>>id2;
       		
       	    if(	!ArtList.article_check(id2))
       	    {
       	    	cout<<"id doesn't exist !!"<<endl;
       	    	break;
			}
			cout<<"please wait!!"<<endl<<endl;
			Article art1,art2;
			art1 = ArtList.get_Art(id1);
			art2 =ArtList.get_Art(id2);
			cout<<"similarity percent is : "<<endl;
			float f = s(art1 ,art2 );
		    cout<<f	;

			break;     
	    }
       case 5:
       	{

       		break; 
		   }

           break;
       }
   }

    
    
	return 0;
}

string char_to_str(char ch[])
{
	string str="";
	for(int i=0 ; i<strlen(ch); i++)
	{
		str+=ch[i];
	}
	return str;

}
