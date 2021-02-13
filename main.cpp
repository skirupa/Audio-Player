//MUSIC PLAYER SYSTEM


#pragma comment(lib, "winmm.lib")
#include<iostream>
#include<string.h>
#include<Windows.h>
#include<mmsystem.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream>

int counts=0;
using namespace std;
struct node
{
	char data[100];
	struct node *next,*prev;
};
class linkedlist
{
	node *start,*tail;
public:
	linkedlist()
	{
		start=tail=NULL;
	}
	void insert_first(char [],int i);
	void play();
	void display();
	void previous();
	void next();
	void disp();
	void del_song();
	void search_song();
	void shuffle();
	node* interleave(node *start,node *result);
	node* split(node *start);
	void tofile(char item[100],int i);
	void remove_node(node *ptr);
};
struct node *prt;
class Queue
{
    node *front,*rear;
public:
    Queue()
    {
        front=rear=NULL;
    }
    void enqueue();
    void disp_queue();
    void playQ();
};
void Queue::enqueue()
{
    char song[100];
    cout<<"\nChoose song you wish to Queue...";
    cin>>song;
    node *temp=new node;
    strcpy(temp->data,song);
    temp->prev=NULL;
    temp->next=NULL;
    if(rear==NULL)
    {
        front=rear=temp;
    }
    else
    {
        temp->prev=rear;
        rear->next=temp;
        rear=temp;
    }
}
void Queue::disp_queue()
{
    cout<<"\nList of songs added to queue..."<<endl;
	struct node *temp;
	if(front==NULL && rear==NULL)
    {
        cout<<"\n\tYour Queue is empty"<<endl;
        return;
    }
    else
    {
        temp=front;
        while(temp!=NULL)
        {
            cout<<temp->data<<endl;
            temp=temp->next;
        }
    }
}
void Queue::playQ()
{
    cout<<"\nPlaying songs in the queue..."<<endl;
    if(front==NULL)
    {
        cout<<"\n\tYour Queue is empty"<<endl;
    }
    while(front!=NULL)
    {
        node *temp;
        cout<<"\n\tNow Playing "<<front->data<<"...\n"<<endl;
        PlaySound(TEXT(front->data), NULL, SND_SYNC);
        temp=front;
        front=front->next;
        if(front==NULL)
        {
            rear=NULL;
        }
        delete(temp);
    }
}
//SHUFFLING SONGS
node* linkedlist::split(node *start)
{
    struct node *slow_ptr=start;
    struct node *fast_ptr=start;
    if(start!=NULL)
    {
        while(fast_ptr!=NULL && fast_ptr->next!=NULL)
        {
            fast_ptr=fast_ptr->next->next;
            slow_ptr=slow_ptr->next;
        }
    }
    node *result=slow_ptr->next;
    slow_ptr->next=NULL;
    return result;
}
node* linkedlist::interleave(node *start,node *result)
{
    struct node *res,*temp1,*temp2;
    if(!start)
    {
        return result;
    }
    if(!result)
    {
        return start;
    }
    res=start;
    while(start!=NULL && result!=NULL)
    {
        temp1=start->next;
        temp2=result->next;
        if(start->next)
        {
            result->next=start->next;
        }
        start->next=result;
        start=temp1;
        result=temp2;
    }
    return res;
}
void linkedlist::shuffle()
{
    node *head=split(start);
    node *start1=interleave(start,head);
    node *ptr=start1;
    cout<<"\nShuffled list..."<<endl;
    while(ptr!=NULL)
    {
        cout<<ptr->data<<endl;
        ptr=ptr->next;
    }
    cout<<"\nPlaying shuffled songs for u..."<<endl;
    while(start1!=NULL)
    {
        cout<<"\n\tNow Playing\t"<<start1->data<<"...\n"<<endl;
        PlaySound(TEXT(start1->data), NULL, SND_SYNC);
        start1=start1->next;
    }
}
void linkedlist::tofile(char item[100],int i)
{
    ifstream f1;
    ofstream f2;
    char line[100];
    int flag=0;
    if (i==1)
    {
        f1.open("Playlist.txt",ios::in);
        if(!f1.is_open())
        {
            f2.open("Playlist.txt",ios::app);
            f2.write(item,100);
            return;
        }
        f1.read(line,100);
        while(!f1.eof())
        {
            int res=strcmp(line,item);
            if(res==0)
            {
                flag=1;
            }
            f1.read(line,100);
        }
        if(flag==0)
        {
            f2.open("Playlist.txt",ios::app);
            f2.write(item,100);
        }
        f1.close();
        f2.close();
    }
    else if(i==2)
    {
        f1.open("Favourites.txt",ios::in);
        if(!f1.is_open())
        {
            f2.open("Favourites.txt",ios::app);
            f2.write(item,100);
            return;
        }
        f1.read(line,100);
        while(!f1.eof())
        {
            int res=strcmp(line,item);
            if(res==0)
            {
                flag=1;
            }
            f1.read(line,100);
        }
        if(flag==0)
        {
            f2.open("Favourites.txt",ios::app);
            f2.write(item,100);
        }
        f1.close();
        f2.close();
    }
}
void linkedlist::insert_first(char item[100],int i)
{
	struct node *n;
	n=new node;
	strcpy(n->data,item);
	tofile(item,i);
	n->prev=NULL;
	n->next=NULL;
	counts++;
	if(start==NULL)
	{
		start=tail=n;
	}
	else
	{
		start->prev=n;
		n->next=start;
		start=n;
	}
}
void linkedlist::disp()
{
    node *ptr=start;
    while(ptr!=NULL)
    {
        cout<<"\n\tNow Playing\t"<<ptr->data<<"...\n"<<endl;
        PlaySound(TEXT(ptr->data), NULL, SND_SYNC);
        ptr=ptr->next;
    }
}
void linkedlist::play()
{
	prt=start;
	int ch1;
	if(prt==NULL)
    {
        cout<<"\nNo Songs in Playlist!\n";
        return;
    }
	cout<<"\n\tplaying the "<<prt->data <<" song for u......"<<endl;
	play_mus:
	PlaySound(TEXT(start->data), NULL, SND_SYNC);
	cout<<"\n1.STOP\n2.NEXT";
	cin>>ch1;
	cout<<"\n\tpress any key to continue";
	cin.ignore();
	cin.get();
	if(ch1==1)
	{
		PlaySound(0,0,0);
		cout<<"\n\tTo restart music"<<endl;
		system("pause");
		system("cls");
		goto play_mus;
	}
	else if(ch1==2)
	{
		system("cls");
		next();
	}
}
void linkedlist::display()
{
	system("cls");
	struct node *ptr;
	ptr=start;
    cout<<"\nSongs list: "<<endl;
    if(ptr==NULL)
    {
        cout<<"No Songs!\n";
        return;
    }
    do
	{   cout<<"\n\t"<<ptr->data<<endl;
		ptr=ptr->next;
	}while(ptr!=NULL);
}
void linkedlist::previous()
{
	int ch1;
pre:
    prt=prt->prev;
    cout<<"\n\tplaying the "<<prt->data<<" song for u......"<<endl;
    PlaySound(TEXT(prt->data), NULL, SND_SYNC);
	cout<<"\n1.STOP\n2.NEXT\n3.PREVIOUS";
	cin>>ch1;
	cout<<"\n\tpress any key to continue";
	cin.ignore();
	cin.get();
	if(ch1==1)
	{
        PlaySound(0,0,0);
    }
    else if(ch1==2)
    {
        system("cls");
        next();
    }
    else
    {
        system("cls");
        goto pre;
    }
}
void linkedlist::next()
{
	int ch1;
label:
		prt=prt->next;
		cout<<"\n\tplaying the "<<prt->data<<" song for u......"<<endl;
		PlaySound(TEXT(prt->data), NULL, SND_SYNC);
        cout<<"\n1.STOP\n2.NEXT\n3.PREVIOUS";
        cin>>ch1;
        cout<<"\n\tpress any key to continue";
        cin.ignore();
        cin.get();
	if(ch1==1)
	{
        PlaySound(0,0,0);
    }
    else if(ch1==2)
    {
        system("cls");
        goto label;
    }
    else if(ch1==3)
    {
        system("cls");
        previous();
    }
}
void linkedlist::remove_node(node *ptr)
{
     if(start==tail)
     {
         start=tail=NULL;
     }
     else if(ptr==start)
     {
         start=ptr->next;
         start->prev=NULL;
     }
     else if(ptr==tail)
     {
         tail=ptr->prev;
         tail->next=NULL;
     }
     else
    {
        ptr->prev->next=ptr->next;
        ptr->next->prev=ptr->prev;
    }
}
void linkedlist::del_song()
{
    char song[100];
    display();
    cout<<"\n\tChoose song you wish to delete- ";
    cin>>song;
    int flag=0;
    struct node *temp;
    temp=start;
    while(temp!=NULL)
    {
        if(strcmp(temp->data,song)==0)
        {
            cout<<"\n\tSong Found"<<endl;
            //delete_file(temp->data);
            //temp->prev->next=temp->next;
            //temp->next->prev=temp->prev;
            remove_node(temp);
            delete(temp);
            flag++;
            cout<<"\n\tSong deleted"<<endl;
            break;
        }
        else
        {
            temp=temp->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\tSong Not found"<<endl;
    }
}
void linkedlist::search_song()
{
    char song[100];
    cout<<"\n\tEnter song To be Searched- ";
    cin>>song;
    int flag=0;
    node *temp;
    temp=start;
    while(temp!=NULL)
    {
        if(strcmp(temp->data,song)==0)
        {
            cout<<"\n\tSong Found"<<endl;
            cout<<"\n\tPlaying  "<<temp->data<<" for u..."<<endl;
            PlaySound(TEXT(temp->data), NULL, SND_SYNC);
            flag++;
            break;
        }
        else
        {
            temp=temp->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\tSong Not found"<<endl;
    }
}
int main()
{
    cout<<"\t\t\t\t\t\t _________________________________________________________________ \n";
    cout<<"\t\t\t\t\t\t|                                           	                  |\n";
    cout<<"\t\t\t\t\t\t|                                                                 |\n";
    cout<<"\t\t\t\t\t\t|                                                                 |\n";
    cout<<"\t\t\t\t\t\t|            WELCOME TO THE MUSIC PLAYER SYSTEM                   |\n";
    cout<<"\t\t\t\t\t\t|                                                                 |\n";
    cout<<"\t\t\t\t\t\t|                                                                 |\n";
    cout<<"\t\t\t\t\t\t|_________________________________________________________________|\n\n";
	linkedlist l,r;
    struct node *start=new node;
	music:
	int j=1,k=1,choice,a;
	char item[100];
    cout<<"\n\tDo you want to add a song to your playlist(1/0)";
	cin>>a;
	if (a==1)
	{
	while(j)
	{
        cout<<"\n\t\tsong name: ";
        cin>>item;
        l.insert_first(item,1);
        cout<<"\n\tDo you want to continue to add songs(1/0)";
        cin>>j;
	}
	}
	while(k)
	{
	system("cls");
	cout<<"\n\t\t\t\t\t\t\t\t***MUSIC  PLAYER  SYSTEM***\n"<<"\n\t---Functionalities available"<<endl;
	cout<<"\n\t1.play your playlist\n\t2.Display your playlist\n\t3.Total songs\n\t4.Add songs\n\t5.Add to Favourites\n\t6.Delete song\n\t7.Search song\n\t8.Shuffle all\n\t9.Add to Queue\n\t10.Display playlist files\n\t";
    cout<<"\n\n\n\tYour Choice"<<endl;
    cin>>choice;
	switch(choice)
	{
    case 1: {
                system("cls");
                l.play();
                break;
            }
	case 2: {
                system("cls");
                cout<<"\n\tList of songs in the playlist...";
                l.display();
                break;
			}
	case 3: {
                system("cls");
                cout<<"\n\tyou have "<<counts<<" songs in your list\n";
                break;
            }
	case 4: {
                system("cls");
                goto music;
                break;
            }
    case 5: {
                system("cls");
                cout<<"\n\tList of songs available...";
                l.display();
                int a,b,j=1;
                char item[100];
                cout<<"\nDo you want to add a song to your favourite playlist(1/0)";
                cin>>a;
                if(a==1)
                {
                while(j)
                {
                    cout<<"\n\tsong name: ";
                    cin>>item;
                    r.insert_first(item,2);
                    cout<<"\nDo you want to continue to add songs to your favourites(1/0)";
                    cin>>j;
                }
                }
                cout<<"\nDo you want to display your favourite playlist(1/0)";
                cin>>b;
                if(b==1)
                {
                    r.display();
                }
                int p;
                cout<<"\nDo you want to play your favourites(1/0)"<<endl;
                cin>>p;
                if(p==1)
                {
                    r.disp();
                }
                break;
            }
    case 6: {
                system("cls");
                l.del_song();break;
            }
    case 7: {
                system("cls");
                l.search_song();break;
            }
    case 8: {
                system("cls");
                l.shuffle();break;
            }
    case 9: {
                system("cls");
                Queue q;
                int h=1;
                while(h)
                {
                    cout<<"\n\tList of songs: "<<endl;
                    l.display();
                    q.enqueue();
                    cout<<"\n\tDo you want to queue more(1/0)";
                    cin>>h;
                }
                q.disp_queue();
                q.playQ();break;
            }
    case 10:{
                system("cls");
                int in;
                cout<<"\n(1) Playlist file\n(2) Favourites file"<<endl;
                cin>>in;
                if(in==1)
                {
                    ifstream f("Playlist.txt");
                    if(!f)
                    {
                        cout<<"PLAYLIST NOT FOUND"<<endl;break;
                    }
                    cout<<"\nList of all songs included into the system: "<<endl;
                    char line[100];
                    f.read(line,100);
                    while(!f.eof())
                    {
                        cout<<line<<endl;
                        f.read(line,100);
                    }
                }
                else if(in==2)
                {
                    ifstream f("Favourites.txt");
                    if(!f)
                    {
                        cout<<"FAVOURITES NOT FOUND"<<endl;break;
                    }
                    cout<<"\nList of all songs included into the favourites: "<<endl;
                    char line[100];
                    f.read(line,100);
                    while(!f.eof())
                    {
                        cout<<line<<endl;
                        f.read(line,100);
                    }
                }
            }
    }
	cout<<"\nDo you want to continue(1/0)"<<endl;
	cin>>k;
	}
}
