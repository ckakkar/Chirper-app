#include <iostream>
#include <string>
#include <iomanip> //to use the width function 
#include <fstream>  //File input/output

using namespace std;

#define MSG 180
const char heart[] = "\xe2\x99\xa5";
const char arrow[] = "\xe2\x86\x94";

struct post      //indivisually defined post
{
    string message;
    int num_likes;
    bool likes;
    bool reChirp;
    post *previous;
    post *next;
};
typedef post* postPtr;

class Chirp;

class Chirp
{
private:
    string user;
    string display_name;
    postPtr head; //head
    
    bool isEmpty();   //post-checks if the list is empty
    void previous_chirp(postPtr &p,bool &flag);   //navigation chirps
    void next_chirp(postPtr &p,bool &flag);
    void display_chirp(postPtr it, int i); //prints the post 
    void add_like(postPtr &p);      //adds like to the post

    void scroll_thru_posts(postPtr &p); //the objective function to scroll thru posts
    void scroll_my_posts();  //calls scroll thru post
    void change_dn();   //changes the display name 
    bool delete_chirp(postPtr &p);   //removes the post from the directory
    void add_chirp_post(const string& s);    //adds the post to the 

    Chirp *bro; //one friend added via file input
    void scroll_thru_friend_posts();   //implicitly calls the scroll function
    void add_friends();     //adds friend to *bro
    void reChirp(postPtr &p);    //retweets the post

public:
    Chirp(); //constructor
    ~Chirp(); //destructor

    void setup_account();
    void menu();
    void setUser(const string &s);  
    string getUser() const;
    void setDN(const string &s);
    string getDN() const;
};