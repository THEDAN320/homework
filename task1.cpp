#include <fstream>
#include<iostream>
#define SIZE 256

using namespace std;

//data class user
class User{
public:
	string login, password;
	User(string login, string password){
		this->login = login;
		this->password = password;
	}
};

//our service
class Service{
public:
	User* users[SIZE];
	int count_users;
	bool succeful_autorization = 0;
	
	Service(){
		ifstream BD("BD.txt");
		string login, password;
		int i;
		
		//writing our bd to users array
    	for(i = 0; true ;i++){
    	    if(BD.eof()) break;
			BD >> login >> password;
			User* user = new User(login, password);
			this->users[i] = user;
    	}
    	
    	this->count_users = i;
    	BD.close();
	}
	
	//autorization def
	void autorization(){
	    string login,password;
	    int i;
	    
	    do{
	        cout << "\n[0 - Exit]\nEnter your login - ";
	        cin >> login;
	        if(password == "0") return;
	        
	        //find login in bd
	        for(i = 0;true;i++){
	            if(i == count_users){
					cout << "This login not found!\n";
					return;
	        }
	        else if(users[i]->login == login) break;
	    }
	        
	        
	        if(users[i]->login == login) break;
	    }while(true);
	    
	    //input password
	    do{
	        cout << "\n[0 - Exit]\nEnter your password - ";
	        cin >> password;
	        if(password == "0") return;
	        if(users[i]->password == password) break;
	        cout << "This password is wrong!\n";
	    }while(true);
	    
	    this->succeful_autorization = 1;
	}
	
	//register
	void registration(){
	    string login,password;
	    
	    //input login
	    do{
	        cout << "\n[0 - Exit]\n[Minium 4 simbols!]\nEnter your login - ";
	        cin >> login;
	        if(login == "0") return;
	        for(int i = 0;i < count_users;i++){
	            if(users[i]->login == login){
	                cout << "This login is busy!\n";
	                return;
	            }
	        }
	        if(login.size() >= 4) break;
	    }while(true);
	    
	    //input password
	    do{
	        cout << "\n[0 - Exit]\n[Minium 8 simbols!]\nEnter your password - ";
	        cin >> password;
	        if(password == "0") return;
	        if(password.size() >= 8) break;
	    }while(true);
	    
	    //create new users
	    User* user = new User(login,password);
	    this->users[count_users] = user;
	    
	    //update bd
	    ofstream BD("BD.txt",ios::app);
	    BD << users[count_users]->login << " " << users[count_users]->password << "\n";
	    BD.close();
	    this->count_users++;
	    cout << "Succeful registration!\n";
	}
};

int main(){
    char choice;
    Service* servise = new Service();
    cout << "Hello!";
    
    //while autorization not succeful
    do{
        cout << "\nYou want registration[1] or autorization[2]? - ";
        cin >> choice;
        if(choice == '1') servise->registration();
        else if(choice == '2') servise->autorization();
    }while(true and !servise->succeful_autorization);
    
    cout << "Succeful autorization!";
	return 0;
}
