#include "Chirper.h"


bool Chirp::isEmpty()
{
    return this->head == nullptr;
}

void Chirp::previous_chirp(postPtr &p,bool &flag) 
{
    if(p->previous==nullptr) //checks if navigation is posible 
    {
        cerr<<"Nothing above it"<<endl;
        flag=false;
        return;
    }
    p=p->previous;
}

void Chirp::next_chirp(postPtr &p,bool &flag)
{
    if(p->next==nullptr)//checks if navigation is posible 
    {
        cerr<<"Nothing ahead it"<<endl;
        flag=false;
        return;
    }
    p=p->next;
}

void Chirp::setup_account()  //calls add post for getting the user started 
{
    cout<<"         Welcome to Chirper!!"<<endl;
    cout<<"Please be respectful of other's privacy."<<endl<<endl;
    string name, uname;
    cout<<"Enter your username(it can't be changed later): ";
    getline(cin,uname);

    cout<<"Preferably you would like something unique for your display name!!"<<endl;
    cout<<"Enter: ";
    getline(cin,name);

    setDN(name);
    setUser(uname);

    cout<<"Let's match you up with some of your friends!!!"<<endl;
    this->add_friends();

    string s;

    cout<<"\n\n\n\n\nlet's get you chirping, add your first post: "<<endl;
    getline(cin,s);

    s.resize(MSG);
    add_chirp_post(s);
}

Chirp::Chirp()      
{
    this->head=nullptr;
}
Chirp::~Chirp()// deletes the whole list 
{
    postPtr current=this->head;
    postPtr next;

    while (current!=nullptr)
    {
        next=current->next;
        delete current;
        current = next;
    }
    this->head=nullptr;
}
void Chirp::scroll_my_posts()
{
    postPtr it=this->head;
    if(it==nullptr)
    {
        cerr<<"Nothing to go through";
        return;
    }
    cout<<"User: "<<this->getDN()<<endl;
    scroll_thru_posts(it);
}
void Chirp::scroll_thru_friend_posts()
{
    postPtr it=this->bro->head;
    if(it==nullptr)
    {
        cerr<<"Nothing to go through";
        return;
    }
    cout<<"User: "<<this->bro->getDN()<<endl;
    scroll_thru_posts(it);
}
void Chirp::reChirp(postPtr &p)
{
    this->add_chirp_post(p->message);
    p->reChirp=true;
}
bool Chirp::delete_chirp(postPtr &p)
{
    if(p==nullptr || this->head==nullptr)
    {
        cerr<<"the list is empty!!"<<endl;
        return false;
    }
    if (this->head==p)
        this->head=p->next;

    if (p->next!=nullptr)
        p->next->previous=p->previous;

    if (p->previous!=nullptr)
        p->previous->next=p->next;
    free(p);
    return true;
}
void Chirp::add_chirp_post(const string& s) //checks if the list is empty or not then acordib gly inputs the post
{
    if(this->isEmpty())
    {
        this->head=new post;
        this->head->message=s;
        this->head->num_likes=0;
        this->head->reChirp=false;
        this->head->likes=false;
        this->head->previous=nullptr;
        this->head->next=nullptr;
    }
    else
    {
        postPtr new_node=new post();
        new_node->message=s;
        new_node->num_likes=0;
        new_node->reChirp=false;
        new_node->likes=false;

        new_node->next=this->head;
        new_node->previous=nullptr;

        this->head->previous=new_node;
        head=new_node;
    }
}
void Chirp::scroll_thru_posts(postPtr &p)
{
    postPtr it=p;
    int count=1;
    char option;
    while(true)
    {
        lab:
        display_chirp(it,count);
        cout<<"(p)revious     (n)ext"<<endl;
        cout<<"(L)ike     (R)etweet     (D)elete   or   E(x)it"<<endl;
        cin>>option;
        if(+option==76 || +option==108)
        {
            add_like(it);
            goto lab;
        }
        else if(+option==68 || +option==100)  //delting the post 
        {
            if(delete_chirp(it))
                cout<<"Deletion successful!"<<endl;
            else
                cerr<<"Error while deletion!"<<endl;
            return;
        }
        else if(+option==80 || +option==112)    //navigates back
        {
            bool flag=true;
            this->previous_chirp(it,flag);
            if(flag)
                count--;
            goto lab;
        }
        else if(+option==78 || +option==110)  //navigates ahead
        {
            bool flag=true;
            this->next_chirp(it,flag);
            if(flag)
                count++;
            else
                return;
            goto lab;
        }
        else if(+option==82 || +option==114)  //rechirps the post
        {
            this->reChirp(it);
            cout<<"\nThis was chirped to your user"<<endl;
            return;
        }
        else if(+option==88 || +option==120)  //returns 
        {
            cout<<"\n\nSee ya!!"<<endl;
            return;
        }
        else
        {
            char op;
            cerr<<"Command not recoganized!"<<endl;
            cout<<"Do you want to try again?(Y/N)"<<endl;
            cin>>op;
            if(+option==89 || +option==121)
            {
                cout<<"Sure!!!"<<endl;
                goto lab;
            }
        }
        count++;

    }
}
void Chirp::add_like(postPtr &p)
{
    p->num_likes++;
    p->likes=true;
}
void Chirp::change_dn()
{
    string dn;
    cout<<"Trying something new?? Great"<<endl;
    cout<<"Enter your new username: ";
    getline(cin,dn);
    this->setDN(dn);
}
void Chirp::menu()
{
    char num;
    label:
    bab:
    cout<<"\n\n\n\n\n";
    cout<<"Yo bruh, Watcha tryna do today?\n"<<endl;
    cout<<"1) Add a post"<<endl;
    cout<<"2) Scroll through your posts"<<endl;
    cout<<"3) Scroll through friend’s posts"<<endl;
    cout<<"4) Change your display name"<<endl;
    cout<<"5) Exit App"<<endl<<endl;

    cout<<"Select the number: ";
    cin>>num;
    cin.ignore();
    if(+num!=49 && +num!=50 && +num!=51 && +num!=52 && +num!=53)
    {
        cerr<<"Bro, select from the given options only!"<<endl;
        goto label;
    }

    switch(+num)
    {
        case 49:
        {
            string s;

            cout<<"\n\n\n\n\nGo ahead add your post: "<<endl;
            getline(cin,s);

            s.resize(MSG);
            add_chirp_post(s);

            break;
        }
        case 50:
        {
            scroll_my_posts();
            break;
        }
        case 51:
        {
            scroll_thru_friend_posts();
            break;
        }
        case 52:
        {
            change_dn();
            break;
        }
        case 53:
        {
            cout<<"Bye bro!"<<endl;
            return;
        }
    }
    goto label;
}
void Chirp::setUser(const string &s)
{
    this->user=s;
}
string Chirp::getUser() const
{
    return this->user;
}
void Chirp::setDN(const string &s)
{
    this->display_name=s;
}
string Chirp::getDN() const
{
    return this->display_name;
}
void Chirp::add_friends()
{
    ifstream fin("/Users/cyruskakkar/Downloads/pep.txt"); // please change the directory if needed 
    if(fin.fail())
    {
        cout << "Can not find the specified file\n";
        exit(1);
    }

    string word;
    getline(fin,word);
    bro=new Chirp;
    bro->setUser(word);
    fin.ignore();

    getline(fin,word);
    bro->setDN(word);
    fin.ignore();

    while(!fin.eof())//end of file functionality
    {
        string line;
        getline(fin,line);

        line.resize(MSG); //as a precaution
        bro->add_chirp_post(line);
    }
}


void Chirp::display_chirp(postPtr it, int i)
{
    int count = 0;
    cout <<" _______________________________________________________" << endl; //55x
    cout << "|"<< setw(25) << right << ">>>>> Post #" << i << " <<<<"<< setw(24) << "|" << endl;
    cout << "| ";
    for(int j = 0; j < it->message.length(); j++){
        cout << it->message[j];
        count++;
        if((count > 45 && it->message[j] == ' ') || it->message[j+1] == '\0')
        {
            for(int k = 0; k < 53-count; k++)
            {
                cout << " ";
            }
            cout << "|" << endl;
            count = 0;
            if(it->message[j+1] == '\0')
                break;
            cout << "| ";
        }
    }
    cout << "\tLikes: ";
    if(it->likes)
        cout << heart << it->num_likes << "\t";
    else
        cout << "\t";
    cout << "\tReChirps: ";
    if(it->reChirp)
        cout << arrow << endl;
    else cout << endl;
    cout <<" _______________________________________________________\n\n"; //55x
}
int main()
{
    Chirp ch;
    ch.setup_account(); //setting up the account
    ch.menu();  //calls the menu for further functionality 
    cout<<"See you next time\n";
    cout<<arrow;
    return 0;
}