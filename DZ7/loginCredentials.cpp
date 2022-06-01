#include <iostream>
#include<regex>
using namespace std;

class LoginCredentials {
private:
    string confirmPassword;
protected:
    string email, password;
public:
    LoginCredentials(): email{}, password{}, confirmPassword{} {}
    
    /*prosljeđujemo email, password*/
    LoginCredentials(const string& email, const string& password): 
        email{email}, password{password} {}
    ~LoginCredentials() = default;

    bool validEmail() const {
        regex emailRegex{"(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"};
        return regex_match(email, emailRegex); // provjeravamo jeli email, oblika emailRegex
    }

    // ispis samo emaila
    friend ostream& operator<<(ostream& buffer, const LoginCredentials&); // friend 
};

ostream& operator<<(ostream& os, const LoginCredentials& lc) {
    return os << "Email: " << lc.email;
}

class Account: public LoginCredentials {
protected:
    string username;
public:
    Account(): LoginCredentials{}, username{} {}

    /*prosljeđujemo username, email i password*/
    Account(const string& email, const string& password, const string& username): LoginCredentials{email, password}, username{username} {}
    ~Account() = default;

    string getUsername() const { return username; }
    string getEmail() const { return email; }

    friend ostream& operator<<(ostream&, const Account&);
};


// kontaj kako smo proslijedili ostream od Login Credentials, mogli smo i na klasicni nacin
ostream& operator<<(ostream& os, const Account& lc) {
    return os << (LoginCredentials)lc << ", username: " << lc.username;   
}


int main ()
{
    LoginCredentials lc{"jtodic@mathos.hr", "123456"};
    Account acc{"jtodic@mathos.hr", "123456", "jtodic"};

    cout << acc << "\n";

    return 0;
}