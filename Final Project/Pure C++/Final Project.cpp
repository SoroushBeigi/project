#include <bits/stdc++.h>
using namespace std;
vector<string> split(string stock_name)
{
	string str="" ; 
	vector<string>s;
	while(true)
	{
		str="" ;
		for(int i=0; i<stock_name.size() ;i++)
		{
			if(stock_name[i] != ' ') str+=stock_name[i];
			else if(stock_name[i]==' ')
			{
				stock_name.erase(0,str.length()+1);
				s.push_back(str);
				break;
			}
		}
		if(stock_name=="")break;
	}
	return s;
	
}
class Stock{
    
    string symbol,name ;
    double price,market_cap;
    
    public :
    	Stock(string syb , string na , double pr , double mar):
    		symbol(syb) , name(na) , price(pr) , market_cap(mar)
    		{}
    	void print_stock()
    	{
    		cout<<symbol<<"  &  "<<name<<"  &  "<<price<<"  &  "<<market_cap<<endl;
		}
	
    	
    friend class AccountList;
    friend class StockList;
    friend class Account;


};
class StockList
{
	static int Num ;
	vector<Stock>stocks_total;
	vector<vector<string>> stock_market;
	public:
		void read_csv()
		{
				string fname="stock_market_data.csv",line, word;
	            vector<string> row;
	            fstream file (fname, ios::in);
	            if(file.is_open())
                {
    				while(getline(file, line))
        			{
        				row.clear();
						stringstream str(line);
 
						while(getline(str, word, ','))
							row.push_back(word);
						stock_market.push_back(row);
					}
					Num = stock_market.size()-1;
					for(int i=1 ; i<stock_market.size() ; i++)
					{
						if(stock_market[i].size()==6)
                        {
                         	Stock stock(stock_market[i][1],stock_market[i][2]+ stock_market[i][3] , stod(stock_market[i][4]),stod(stock_market[i][5]));
						    stocks_total.push_back(stock);
						}
						else
						{
							Stock stock(stock_market[i][1],stock_market[i][2],
						                stod(stock_market[i][3]) , stod(stock_market[i][4]));
						    stocks_total.push_back(stock);
						}

					}
				}
	
				else cout<<"Could not open the file"<<endl;
				file.close();
		}
		void show_total_stocks()
		{
			cout<<endl;
        	for(int i= 0; i<stock_market.size() ; i++)
        	{
        		for(int j=0 ; j<stock_market[i].size() ; j++) cout<<stock_market[i][j]<<"   ";
        		cout<<endl;
			}
        	
		}
		void print()
		{
			for(int i=0 ; i<Num  ; i++)
			{
				cout<<i<<stocks_total[i].symbol<<" - "<<stocks_total[i].name<<" - "<<stocks_total[i].price<<" - "<<stocks_total[i].market_cap<<endl;
			}
		}
		Stock get_stock(string sym)
		{
			for(int i=0 ;i<stocks_total.size() ;i++)
			{
				if(stocks_total[i].symbol == sym)
				return stocks_total[i];
			}
		}
		friend class AccountList ; 
};
class Account{
    
    string name,id,acc_num,shaba,username,password;
    double debt,balance,stock_total;
    vector<Stock> stocks;

    public:
    Account(){}
    Account(string u,string p){
        username=u; password=p;  
        
        debt=0; balance=0;stock_total=0;
        name = "NULL",id = "NULL",acc_num="NULL";shaba="NULL";
        stocks.clear();
    }
    void get_info(string n , string i ,string acc ,string sh , double d , double b , double st  ) //hanouz kamel nist
    {
    	name = n ; id = i ; acc_num = acc ; shaba = sh;
    	debt = d ; balance = b ; stock_total = st ;
	}
    
    void accStock(Stock st){
        stocks.push_back(st);
    }

    void deposit(double val){
        balance += val;
        cout<<"deposit was done!"<<endl;
        
    }
    void withdrawal(double val){
		balance -=val;
		cout<<"withdrawal was done!"<<endl;
    	
    }
    void add_stock(Stock st)
    {
    	stocks.push_back(st);
	}
    
    
    void print_shares()
    {
    	
    	cout<<username<<" : "<<endl;
    	for(int i=0 ; i<stocks.size();i++)
    	{
    	    stocks[i].print_stock();
		}
    	
	}
	void buy_stock(Stock st)
	{
		double x = st.price;
		if(x>balance)
		{
			cout<<"you don't have enough money !!"<<endl;
		}
		else
		{
			balance = 0;
			stocks.push_back(st);
			cout<<"buying is successfull !!"<<endl;
		}
	}
	void sell_stock(Stock st)
	{
		double x = st.price;
		balance += x;
		int i = 0;
		for( ; i<stocks.size() ; )
		{
			if(stocks[i].symbol==st.symbol) break;
			i++;
		}
		stocks.erase(stocks.begin()+i); 
	}
	string stock_str()
	{
		string s ="";
		for(int i=0 ;i<stocks.size() ;i++)
		{
			s+=stocks[i].symbol;
			s+=" ";
		}
		return s;
	}
	friend class AccountList;
};

class AccountList
{
    static int Num;
    vector<vector<string>> accounts;
    //vector<Account> account_list;
    
	public:
    void read_csv()
    {
    	string fname="accounts.csv";
		vector<string> row;
		string line, word;
		fstream file (fname, ios::in);
		if(file.is_open())
    	{
    		while(getline(file, line))
        		{
        		row.clear();
				stringstream 
				str(line);
 
				while(getline(str, word, ','))
				row.push_back(word);
				accounts.push_back(row);
				}
			Num = accounts.size()-1;
			file.close();    
		}
	
		else { cout<<"Could not open the file here"<<endl; exit(0);}
	}
	void show_accounts()
	
	{
		for(int i=0; i<accounts.size() ; i++)
		{
			for(int j=0 ; j<accounts[i].size() ; j++) cout<<accounts[i][j]<<"    ";
			cout<<endl;
		}
	}
    void addAccount(Account acc)
	{
    	vector<string> row; Num ++ ;
    	row.clear();
    	row.push_back(to_string(Num));
    	row.push_back(acc.username);
    	row.push_back(acc.password);
    	row.push_back(acc.name);
    	row.push_back(acc.id);
    	row.push_back(acc.acc_num);
    	row.push_back(acc.shaba);
    	row.push_back(to_string(acc.debt));
    	row.push_back(to_string(acc.balance));
    	row.push_back(to_string(acc.stock_total));
    	string str="NULL";
		row.push_back(str);
    	accounts.push_back(row);
    	
    }
    void set_info(string User , string n , string ii ,string a ,string s)
    {
    	for(int i=1 ; i<accounts.size() ; i++)
    	{
    		if(accounts[i][1] == User)
    		{
    			accounts[i][3] = n ;
    			accounts[i][4] = ii;
    			accounts[i][5] = a ;
    			accounts[i][6] = s;
    			string str = "" ;
    			cout<<"update shod !"<<endl;
				break;	
			}
		}
	}
    void write_csv()
    {
    	fstream f("accounts.csv", ios::out | ios::trunc);

    	for(int i=0 ; i<accounts.size() ; i++)
    	{
    		for(int j=0 ; j<accounts[i].size() ; j++)
    		{
    			f<<accounts[i][j]<<",";
			}
			f<<endl;
		}
		f.close();
	}
    void update(Account acc , string str)
    {
    	for(int i=0; i<accounts.size() ; i++)
    	{
    		if(accounts[i][1]== acc.username) 
			{
    			accounts[i][1] = acc.username;
    			accounts[i][2] = acc.password;
    			accounts[i][3] = acc.name;
    			accounts[i][4] = acc.id;
    			accounts[i][5] = acc.acc_num;
    			accounts[i][6] = acc.shaba;
    			accounts[i][7] = to_string(acc.debt);
    			accounts[i][8] = to_string(acc.balance);
    			accounts[i][9] = to_string(acc.stock_total);
    			if(str!="NULL") accounts[i][10] = str;
    			break;

    			}
		}
    	
	}
	
    bool register_check(string user){
        for(int i=1; i<accounts.size();i++){
            if(user==accounts[i][1]){
                return false;
            }
        }
        return true;
    }
    bool login_check(Account acc){
        for(int i=1; i<accounts.size();i++){
            if(acc.username==accounts[i][1] && acc.password==accounts[i][2]){
                return true;
            }
        }
        return false;
    }
    bool info_check(string user)
    {
    	for(int i= 1; i<accounts.size() ; i++)
    	{
    		if(accounts[i][1]==user)
    		{
    			if( accounts[i][3]=="NULL")return false;
    			return true;
			}
		}
		return false;
	}
    Account  logged_in(string user , StockList StList) //return logged_in account and set_stocks;
    {
        for(int i= 1; i<accounts.size() ; i++)
        {
        	if(accounts[i][1]==user)
        	{
        		
        		Account acc(accounts[i][1],accounts[i][2]);
        		acc.get_info(accounts[i][3],accounts[i][4],accounts[i][5],accounts[i][6],
				            stod(accounts[i][7]),stod(accounts[i][8]),stod(accounts[i][9]));
				if(accounts[i][10]!="NULL")
				{

					vector<string>str = split(accounts[i][10]);
	
					for(int z=0 ; z<str.size() ; z++)
					{
						for(int j=1 ; j<StList.stock_market.size();j++)
						{
						
							if(StList.stock_market[j][1]==str[z])
							{
								acc.add_stock(StList.stocks_total[j-1]);
								
							}
							
						}
					}
					return acc;
					
				}
        		return acc;
			}
		}
     }
    
};


int AccountList :: Num = 0;
int StockList :: Num = 0;



//-------------------------------------
// main function 


int main()
{
	string User="NULL",Pass="NULL";
	Account ACCOUNT ;
    AccountList AccList;
    StockList StList;
    AccList.read_csv();
    StList.read_csv();
    bool isLoggedIn = false;
    char sit ; cout<<" start -> enter s : "; cin>>sit;
	while(sit == 's'){
	
		int order;
		cout<<"\n"<<"choose your operations (Menu -> enter 0) : ";
        cin>>order;
    
       switch (order){
        case -2://log out
		    {
		    	User="NULL",Pass="NULL";
            	isLoggedIn=false;
				break;
			}

       case -1://exit
       	{
       		AccList.write_csv();
       		exit(0);
			   break;
       		
		}
		case  0 : // menu
			{
				cout<<"\n"<<"-1 : Exit";

                if(!isLoggedIn){
                cout<<"\n"<<"1 : Create Account"; 
				cout<<"\n"<<"2 : Login"; 
                }else{
				cout<<"\n"<<"-2 : Log Out";
				cout<<"\n"<<"3 : Add Info";
                cout<<"\n"<<"4 : Deposit";
                cout<<"\n"<<"5 : Withdrawal";
                cout<<"\n"<<"6 : Enter Market";
                }
                
                
				cout<<"\n";

				break;
			}

        case 1: // creat account
	   {
            string user,pass;
            cin.ignore(100, '\n');
            while(true){
            cout<<"Enter a Username:"<<endl;
            
            getline(cin,user);
            cout<<"Enter a Password:"<<endl;
            getline(cin,pass);
            if(AccList.register_check(user)){
            Account acc(user,pass);
            AccList.addAccount(acc);
            cout<<"Your account was created successfully!"<<endl;
            AccList.write_csv();
            break;
            }
            cout<<"This username is already used! Please choose another one."<<endl;
            }
            
            

             break;
		}

        case 2: // Login
		{
            cin.ignore(100, '\n');
            while(true)
			{
            cout<<"Enter your Username:"<<endl;
            getline(cin,User);
            cout<<"Enter your Password:"<<endl;
            getline(cin,Pass);
            Account acc(User,Pass);
            if(AccList.login_check(acc)){
                cout<<"You're Logged in!"<<endl;
                isLoggedIn=true;
                break;
            }
            cout<<"Username or password is wrong!\n Please enter them again!"<<endl;
            

            }
             break;}
        case 3: //Add Info & change Info
        	{
        		if(User=="NULL")
        		{
        			cout<<"please log in !!"<<endl;
				}
				else
				{
					string n , ii , s , a;
        			cin.ignore(100, '\n');
        			cout<<"enter your name  : "<<endl;
        			getline(cin , n);
        			cout<<"enter your ID  : "<<endl;
        			getline(cin , ii);
        			cout<<"enter your shaba : "<<endl;
        			getline(cin , s);
        			cout<<"enter your account number : "<<endl;
        			getline(cin , a);
        			AccList.set_info(User , n , ii , a ,s);
        			AccList.write_csv();
        			
        	    }
        	    
        	    break;
			}

        case 4: //deposite
		{ 
		    if(User=="NULL")
        	{
        		cout<<"please log in !!"<<endl;
			}
			else if(!AccList.info_check(User))
			{
				cout<<"please enter your information :(operation number 3 :)) "<<endl;
			}
			else
			{
				double val;
				ACCOUNT = AccList.logged_in(User,StList);
				cout<<"How much money do you want to deposit ? "<<endl;
				cin>>val;
				ACCOUNT.deposit(val);
				AccList.update(ACCOUNT,"NULL");
				AccList.write_csv();
				
			}
				
		    break;
		}
        case 5:
		{
			if(User=="NULL")
        	{
        		cout<<"please log in !!"<<endl;
			}
			else if(!AccList.info_check(User))
			{
				cout<<"please enter your information :(operation number 3 :)) "<<endl;
			}
			else
			{
				double val;
				
				cout<<"How much money do you want to withdraw ? "<<endl;
				cin>>val;
				ACCOUNT.withdrawal(val);
				
				ACCOUNT = AccList.logged_in(User,StList);
	
				AccList.update(ACCOUNT,"NULL");
				AccList.write_csv();
			}
		
		    break;
		}
        case 6:
		{  
		    if(User=="NULL") {
		    	cout<<"you must log in !!"<<endl;
		    	break;
		    }
		    else if(!AccList.info_check(User))
			{
				cout<<"please enter your information :(operation number 3 :)) "<<endl;break;
			}
			
		    cout<<"***Welcome to the Market!***"<<endl;
            cout<<"\n"<<"7 : Buy a Share";
            cout<<"\n"<<"8 : Sell a Share";
            cout<<"\n"<<"9 : View Your Shares";
            cout<<"\n"<<"10 : View All Stocks";

             break;
			 }
		
	
		case 7: //bye a share 
			{
				if(User=="NULL")
        		{
        			cout<<"please log in !!"<<endl;break;
				}
				else if(!AccList.info_check(User))
				{
					cout<<"please enter your information :(operation number 3 :)) "<<endl;break;
				}
				else
				{
					string sym , str ;
					cout<<"enter the symbol of stock !!"<<endl;
					cin>>sym; 
					Stock st = StList.get_stock(sym) ;
					ACCOUNT = AccList.logged_in(User,StList);
					ACCOUNT.buy_stock(st);
					str = ACCOUNT.stock_str();
				

					AccList.update(ACCOUNT,str);
					AccList.write_csv();
					break;
			}
		
		    break;
			}
		case 8: // sell a share
			{
				
			    if(User=="NULL")
        		{
        			cout<<"please log in !!"<<endl;break;
				}
				else if(!AccList.info_check(User))
				{
					cout<<"please enter your information :(operation number 3 :)) "<<endl;break;
				}
				else
				{
					string sym , str ;
					cout<<"enter the symbol of stock !!"<<endl;
					cin>>sym; 
					Stock st = StList.get_stock(sym) ;
					ACCOUNT = AccList.logged_in(User,StList);
					ACCOUNT.sell_stock(st);
					str = ACCOUNT.stock_str();
				

					AccList.update(ACCOUNT,str);
					AccList.write_csv();
					break;
			}
		
		    break;
				
				break;
			}
		case 9: //view your shares
			{
			if(User=="NULL")
        	{
        		cout<<"please log in !!"<<endl;
			}
			else if(!AccList.info_check(User))
			{
				cout<<"please enter your information :(operation number 3 :)) "<<endl;
			}
			else
			{
				
				ACCOUNT = AccList.logged_in(User,StList);
				ACCOUNT.print_shares();
				
			}
				
				break;
			}
        case 10 :  // view all stocks
        {
        	StList.show_total_stocks();
        	break;
		}
		case 11 : {
			
			AccList.show_accounts();
			break;
		}
		case 12 :
			{
				StList.print();
				break ;
			}



       }
    }




     return 0 ;
}
    