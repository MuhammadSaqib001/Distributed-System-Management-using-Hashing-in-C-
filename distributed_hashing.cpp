#include<iostream>
#include "sha1.hpp"
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<cstring>
#include <fstream>
using namespace std;

unsigned long long int hexadecimalToDecimal(string hexVal); 
int hash_algo(int i,int s);
int hash_algo(string l,int s);
void bubbleSort(int arr[], int n); 
void swap(int *xp, int *yp); 
int add_return(string file_path,string value);
bool check_file(string file);
int total_values;
int total_machines;

class machine;

struct node
{
	int hash_value;
	int line_number;
	string path;
	node* left;	
	node* right;
};

struct route_entry
{
	machine* routed;
	route_entry* next;
	route_entry* previous;	
};

machine* target(int id_m);

struct FTp
{
	route_entry* head;
};

class machine_data
{
	public :

	node* root;

	string insert(int hash_key,string value,string file_path)
	{
		return insert_v(hash_key,value,file_path,root);
	}	

	string insert_v(int hash_key,string value,string file_path,node* temp)
	{
	
    		if (root == NULL)
    		{
        		temp = new node;
        		temp->hash_value = hash_key;
        		temp->left = NULL;	
        		temp->right = NULL;
        		root = temp;
        		temp->hash_value=hash_key;
			string file;
			if(check_file(file_path)==1)
			{
        			temp->line_number=add_return(file_path,value);
				temp->path=file_path;
				return file_path;
			}
			else
			{

				int i1=file_path.find(").txt");
				int i2=file_path.find("(");
				int l=i1-i2;
				int i=stoi(file_path.substr(i2+1,l));
				i++;			
				
				file_path.erase(i2);
				file_path.append("(");
				file_path.append(to_string(i));
				file_path.append(").txt");	
				
				file=file_path;
				ofstream MyFile(file);
  				MyFile.close();
				temp->line_number=add_return(file,value);
				temp->path=file;
			
			}
        		return file;
    		}

    		if (temp->hash_value == hash_key)
    		{
    	    		cout << " \n Given number is already present in tree.\n";
    	    		return file_path;
    		}
    		
    		if (temp->hash_value > hash_key)
    		{
        		if (temp->left != NULL)
        		{
        	    		return insert_v(hash_key,value,file_path,temp->left);
        		}
        		else
        		{
        	    		temp->left = new node;
            			temp->left->hash_value = hash_key;
            			temp->left->left = NULL;
            			temp->left->right = NULL;
            			temp->hash_value=hash_key;
				string file;
        			if(check_file(file_path)==1)
				{
        				temp->line_number=add_return(file_path,value);
					temp->path=file_path;
					return file_path;
				}
				else
				{
	
					int i1=file_path.find(").txt");
					int i2=file_path.find("(");
					int l=i1-i2;
					int i=stoi(file_path.substr(i2+1,l));
					i++;			
				
					file_path.erase(i2);
					file_path.append("(");
					file_path.append(to_string(i));
					file_path.append(").txt");	
				
					file=file_path;
					ofstream MyFile(file);
  					MyFile.close();
					temp->line_number=add_return(file,value);
					temp->path=file;
				}
        			return file;
        		}
    		}
    
    		if (temp->hash_value < hash_key)
    		{
        		if (temp->right != NULL)
        		{
        	    		return insert_v(hash_key,value,file_path,temp->right);
        		}
        		else
        		{
            			temp->right = new node;
            			temp->right->hash_value = hash_key;
            			temp->right->left = NULL;
            			temp->right->right = NULL;
            			temp->hash_value=hash_key;
				string file;
        			if(check_file(file_path)==1)
				{
        				temp->line_number=add_return(file_path,value);
					temp->path=file_path;
					return file_path;
				}
				else
				{
					int i1=file_path.find(").txt");
					int i2=file_path.find("(");
					int l=i1-i2;
					int i=stoi(file_path.substr(i2+1,l));
					i++;			
				
					file_path.erase(i2);
					file_path.append("(");
					file_path.append(to_string(i));
					file_path.append(").txt");	
				
					file=file_path;
					ofstream MyFile(file);
  					MyFile.close();
					temp->line_number=add_return(file,value);
					temp->path=file;
				}
        			return file;
        		}
    		}
			return file_path;
	}
	
	void display()
	{
		print_v(root);
	}
		
	void print_v(node* temp)
	{
	
		if(root==NULL)
		{
			return;
		}
		if(temp->left !=NULL)
		{
			print_v(temp->left);
		}
		print(temp);

		if(temp->right!=NULL)
		print_v(temp->right);

		return;	
	}	
	void print(node* tree)
	{
		cout<<tree->hash_value<<endl;	
	}
	
	node* search(int key)
	{
		return search_v(key,root);
	}
	node* search_v(int key,node* temp)
	{
		if(temp==NULL)return root;
		if(temp->hash_value==key)
		{
			return temp;
		}
		else if(temp->hash_value<key)
		{
			return search_v(key,temp->right);
		}
		
		return search_v(key,temp->left);
	}
	
	void delete_v()
	{
			
	}
};

class machine
{
	public :
 
	int id;
	machine* next;
	machine_data avl;
	FTp routing_table;
	string active_file;	

	machine(int s,int i=0)
	{
		id=i;
	}

	void insert_it(int hash_key,string value)
	{
		machine* target=this;
		
		cout<<"Data Key = "<<hash_key<<endl;
		cout<<"Machine Responsible = "<<target->id<<endl;		
		string primary = target->avl.insert(hash_key,value,active_file);
		active_file=primary;
	}

	void delete_it()
	{
		
	}

	string search_it(string key)
	{
		int hash_key=hash_algo(key,total_values);
		node* target=avl.search(hash_key);
	
		ifstream a(target->path);string basic;
		cout<<"File Path = "<<target->path<<endl;
		cout<<"Line Number = "<<target->line_number<<endl;		
		for(int i=0 ; i<target->line_number ; i++)
		{
			basic="";
			getline(a,basic);
		}		
		return basic ;
	}
	
	void route_printing()
	{
		cout<<"The routing Table for Machine ID conatines the pointers to the machines with the ID's : ";
		route_entry* temp=routing_table.head;
		int route_length=ceil(log(total_machines));
		for(int i=0 ; i<route_length ; i++)
		{
			cout<<temp->routed->id<<"\t";
			
			temp=temp->next;
		}
		cout<<endl;
	}
};

class DHT
{
	machine* head;
	machine* tail;
	int permutations;
	int* machine_index;	

	public:
		
	DHT (int s,int n)
	{
		permutations=pow(2,s)-1;
		total_values=permutations;
		if(n==0){total_machines=s/2+1;}
		else 	{total_machines=n;}

		machine_index=new int[total_machines];
		
		for(int i=0 ; i<total_machines ; i++)
		{
			machine_index[i]=-2;
		}
		string str="";
		cout<<"Do you want to assign id to machines manaually : Y/N "<<endl;
		while(1)
		{
			cin>>str;
			if(str=="Y" || str=="y" || str=="N" || str=="n") break;
			else 
			{
				cout<<"You enetered INVALID value . PLz enter a valid value i.e., Y/N ";
			}
		}	
		if(str=="N" || str=="n")
		{
			int counter=1;int i;
			again :
			i=abs(rand());
			i=abs(hash_algo(i,permutations));

			for(int j=0 ; j<total_machines ; j++)
			{
				if(i==machine_index[j])
				{
					goto again;
				}
			}
			machine_index[counter-1]=i;
			head=new machine(permutations,i);
			machine *temp=head;
			while(counter<=(total_machines-1))
			{
				again1 :
				i=abs(rand());
				i=hash_algo(i,permutations);

				for(int j=0 ; j<total_machines ; j++)
				{
					if(i==machine_index[j])
					{
						goto again1;
					}
				}
				machine_index[counter]=i;
				temp->next=new machine(permutations,i);
				temp=temp->next;
				counter++;
			}
			tail=temp;
			tail->next=head;
		}
		else
		{
			int counter=1;int id_m;bool exists=false;
			cout<<"Enter the ID for machine "<<counter<<" : ";
			while(1)
			{
				cin>>id_m;
				for(int i=0 ; i<total_machines ; i++)
				{
					if(id_m==machine_index[i])
					{
						exists=true;
					}
				}
				if(exists==true ){cout<<"A machines with a same ID already exits . PLz enter a valid ID : ";exists=false;}
 				else if (id_m<0 ||id_m>permutations){cout<<"Invalid ID entered ."<<
				" PLz enter a valid ID between 0 & "<<permutations<<" : ";}
				else {break;}		
			}
			machine_index[counter-1]=id_m;
			head=new machine(permutations,id_m);
			machine *temp=head;
			while(counter<=(total_machines-1))
			{
				cout<<"Enter the ID for machine "<<counter+1<<" : ";
				while(1)
				{
					cin>>id_m;
					for(int i=0 ; i<total_machines ; i++)
					{
						if(id_m==machine_index[i])
						{
							exists=true;
						}
					}
				if(exists==true ){cout<<"A machines with a same ID already exits . PLz enter a valid ID : ";exists=false;}
 				else if (id_m<0 ||id_m>permutations){cout<<"Invalid ID entered ."<< 
				"PLz enter a valid ID between 0 & "<<permutations<<" : ";}
				else {break;}				
				}
				machine_index[counter]=id_m;
				temp->next=new machine(permutations,id_m);
				temp=temp->next;
				counter++;
			}
			tail=temp;
			tail->next=head;
		}
		
		bubbleSort(machine_index,n);
		machine* temp=head;
		for(int i=0 ; i<total_machines ; i++)
		{
			temp->id=machine_index[i];
			temp=temp->next;
		}
		string file;temp=head;
		string Id;	

		cout<<"Total_Machines : "<<total_machines<<endl;
		for(int i=0 ; i<total_machines ; i++)
		{
			file="M_";
			Id=to_string(temp->id);
			file.append(Id);
			file.append("(0)");
			file.append(".txt");
			temp->active_file=file;

			ofstream okay;
			okay.open(file);
			okay.close();				
			temp=temp->next;
		}

		temp=head;
		int route_length=ceil(log(total_machines));
		for(int i=0 ; i<total_machines ; i++)
		{
			temp->routing_table.head=new route_entry;
			temp->routing_table.head->next=temp->routing_table.head->previous=NULL;
			temp->routing_table.head->routed=succ(machine_index[i]+1);
			route_entry* temp1=temp->routing_table.head;
			route_entry* temp2;
			for(int j=1 ; j<route_length ; j++)
			{
				temp1->next=new route_entry;
				temp1->next->routed=succ(machine_index[i]+pow(2,j));
				temp2=temp1->next;
				temp2->previous=temp1;
				temp1=temp2;	
			}
			temp1->next=temp->routing_table.head;
			temp->routing_table.head->previous=temp1;
			temp=temp->next;
		}
	}


	void data_insertion(string key , string value)
	{
		cout<<"FRom which machine do you want to intitiate insert query : ";
		int i;cin>>i;
	
		
		int hash_key=hash_algo(key,permutations);
		machine* target=succ(hash_key);
		return target->insert_it(hash_key,value);
	}

	string data_search(string key)
	{
		cout<<"FRom which machine do you want to intitiate search query : ";
		int i;cin>>i;
	
		int hash_key=hash_algo(key,permutations);
		machine* target=succ(hash_key);
		return target->search_it(key);
	}
	
	machine* get_head()
	{
		return head;
	}

	void machine_insertion()
	{
		int *temp1=new int[total_machines+1];
		
		for(int i=0 ; i<total_machines ; i++)
		{
			temp1[i]=machine_index[i];
		}

		string str="";
		cout<<"Do you want to assign id to machines manaually : Y/N "<<endl;
		while(1)
		{
			cin>>str;
			if(str=="Y" || str=="y" || str=="N" || str=="n") break;
			else 
			{
				cout<<"You enetered INVALID value . PLz enter a valid value i.e., Y/N ";
			}
		}	
		if(str=="N" || str=="n")
		{
			int counter=1;int i;
			again :
			i=abs(rand());
			i=abs(hash_algo(i,permutations));

			for(int j=0 ; j<total_machines ; j++)
			{
				if(i==machine_index[j])
				{
					goto again;
				}
			}
			temp1[total_machines]=i;
			machine* in=new machine(permutations,i);
			total_machines++;
			machine_index=temp1;
			tail->next=in;
			tail=in;
			tail->next=head;
		}
		else
		{
			int counter=1;int id_m;bool exists=false;
			cout<<"Enter the ID for machine "<<counter<<" : ";
			while(1)
			{
				cin>>id_m;
				for(int i=0 ; i<total_machines ; i++)
				{
					if(id_m==machine_index[i])
					{
						exists=true;
					}
				}
				if(exists==true ){cout<<"A machines with a same ID already exits . PLz enter a valid ID : ";exists=false;}
 				else if (id_m<0 ||id_m>permutations){cout<<"Invalid ID entered ."<<
				" PLz enter a valid ID between 0 & "<<permutations<<" : ";}
				else {break;}		
			}
			
			temp1[total_machines]=id_m;
			machine* in=new machine(permutations,id_m);
			total_machines++;
			machine_index=temp1;
			tail->next=in;
			tail=in;
			tail->next=head;
		}
		
		bubbleSort(machine_index,total_machines);
		machine* temp=head;
		for(int i=0 ; i<total_machines ; i++)
		{
			temp->id=machine_index[i];
			temp=temp->next;
		}

		temp=head;
		int route_length=ceil(log(total_machines));
		for(int i=0 ; i<total_machines ; i++)
		{
			temp->routing_table.head=new route_entry;
			temp->routing_table.head->next=temp->routing_table.head->previous=NULL;
			temp->routing_table.head->routed=succ(machine_index[i]+1);
			route_entry* temp1=temp->routing_table.head;
			route_entry* temp2;
			for(int j=1 ; j<route_length ; j++)
			{
				temp1->next=new route_entry;
				temp1->next->routed=succ(machine_index[i]+pow(2,j));
				temp2=temp1->next;
				temp2->previous=temp1;
				temp1=temp2;	
			}
			temp1->next=temp->routing_table.head;
			temp->routing_table.head->previous=temp1;
			temp=temp->next;
		}

		string file;temp=head;
		string Id;	

		
	}
	
	machine* succ(int id_m)
	{
		int m=0;		
		if(id_m<machine_index[0]){m=machine_index[0];}

		else if(id_m>machine_index[total_machines-1]){m=machine_index[0];}

		else
		{
			bool exist=false;
			for(int i=0 ; i<total_machines ; i++)
			{
		
			if( id_m == machine_index[i])
				{
					m=machine_index[i];
					exist=true;
				}
			}
			if(exist==false)
			{
				for(int i=0 ; i<total_machines ; i++)
				{
					if (machine_index[i]<id_m && machine_index[i+1]>id_m) 
					{
						m=machine_index[i+1];
					}
				}
			}
		}
		machine* temp=head;
		while(1)
		{
			if(temp->id==m)
			{
				break;
			}
			temp=temp->next;	
		}
		return temp;
	}

	void machine_deletion()
	{
		int *temp1=new int[total_machines-1];

		
		int id_m;bool exists=false;
		cout<<"Enter the ID for machine to be deleted : ";
		again :

		cin>>id_m;
		int counter=total_machines-1;
	
		while(counter+1)
		{
			if(id_m==machine_index[counter])
			{
				exists=true;
				break;
			}
			counter--;
		}

		if(exists!=true){cout<<"PLz enter a valid & existing ID : "; goto again;}	
		int j=0;
		for(int i=0 ; i<total_machines ; i++)
		{
			if(machine_index[i]!=id_m)
			{
				temp1[j]=machine_index[i];
				j++;
			}
		}
		total_machines--;
		machine_index=temp1;

		bubbleSort(machine_index,total_machines);
		machine* temp=head;
		machine* copy=NULL;

		if(head->id == id_m)
		{
			copy=head;
			head=copy->next;

			tail->next=head;
		}
		
		else if(tail->id == id_m)
		{
			temp=head;
			while(1)
			{
				if(temp->next==tail)
				{
					break;
				}
				temp=temp->next;		
			}
			copy=tail;
			temp->next=head;
		}

		else
		{
			temp=head;
			while(1)
			{
				if(temp->next->id==id_m)
				{
					break;
				}
				temp=temp->next;		
			}
			copy=temp->next;
			temp->next=temp->next->next;
			tail->next=head;	
		}
			
		temp=head;
		int route_length=ceil(log(total_machines));

		cout<<"Total Machines : "<<total_machines<<endl;
		for(int i=0 ; i<total_machines ; i++)
		{
			cout<<temp->id<<endl;
			temp=temp->next;
		}
		temp=head;
		for(int i=0 ; i<total_machines ; i++)
		{
			temp->routing_table.head=NULL;	
			temp->routing_table.head=new route_entry;
			temp->routing_table.head->next=temp->routing_table.head->previous=NULL;
			temp->routing_table.head->routed=succ(machine_index[i]+1);
			route_entry* temp1=temp->routing_table.head;
			route_entry* temp2;
			for(int j=1 ; j<route_length ; j++)
			{
				temp1->next=new route_entry;
				temp1->next->routed=succ(machine_index[i]+pow(2,j));
				temp2=temp1->next;
				temp2->previous=temp1;
				temp1=temp2;	
			}
			temp1->next=temp->routing_table.head;
			temp->routing_table.head->previous=temp1;
			temp=temp->next;
		}
	
		temp=head;
		string file;temp=head;
		string Id;
		return ;
	}

};

int main()
{
	srand(time(0));
	int space;
	cout<<"Specify the identifier space : "<<endl;  
	while(1)
	{
		cin>>space;
		if(space>=0) break;
		else 
		{
			cout<<"You enetered INVALID value for the identifier space . Plz enter a valid value : ";
		}
	}

	int n;
	cout<<"Specify the number of machines (Enter 0 to leave it on system) : "<<endl;  
	while(1)
	{
		cin>>n;
		if(n>pow(2,space)-1)
		{
			cout<<"The number of machines can't be greater than max key to be indexed . Plz enter a valid value : ";
		}
		else if(n<0)
		{
			cout<<"You enetered INVALID value for the number of machines . Plz enter a valid value : ";
		}
		else break;
		
	}

	DHT a(space,n);

	machine* na=a.get_head();
	for(int i=0 ;i<n ; i++)
	{
		cout<<na->id<<endl;
		na=na->next;
	}
	na=a.get_head();

	a.machine_deletion();
	/*
	na->route_printing();
	a.data_insertion("19I-0494","Muhammad Saqib");
	a.data_insertion("19I-0474","Haseeb");
	a.data_insertion("19I-0492","Rasib");
	a.data_insertion("19I-0491","Ahmad");
	a.data_insertion("19I-0493","Okays");

	cout<<a.data_search("19I-0491")<<endl;
	cout<<a.data_search("19I-0493")<<endl;
	*/
}

unsigned long long int hexadecimalToDecimal(string hexVal) 
{    
    	int len = hexVal.length(); 
    	unsigned long long int base = 1; 
      
    	unsigned long long int dec_val = 0; 
    	for (int i=len-1; i>=0; i--) 
    	{    
    		if (hexVal[i]>='0' && hexVal[i]<='9') 
    	    	{ 
    	        	dec_val += (hexVal[i] - 48)*base; 
    	        	base = base * 16; 
    	    	}
    	    	else if (hexVal[i]>='a' && hexVal[i]<='f') 
            	{ 
            		dec_val += (hexVal[i] - 87)*base;
            		base = base*16; 
            	} 
    	} 
      
    	return dec_val; 
}

void swap(int *xp, int *yp)  
{  
    	int temp = *xp;  
    	*xp = *yp;  
    	*yp = temp;  
}  
  
void bubbleSort(int arr[], int n)  
{  
    	int i, j;  
    	for (i = 0; i < n-1; i++)
	{      
    		for (j = 0; j < n-i-1; j++)  
		{
        		if (arr[j] > arr[j+1])  
            		swap(&arr[j], &arr[j+1]); 
		}
	} 
}

int hash_algo(string l,int s)
{
	SHA1 a;
    	a.update(l);
    	const string hash = a.final();
	unsigned long long int x=hexadecimalToDecimal(hash);
	int r=x;
	return abs(r%s);
}

int hash_algo(int i,int s)
{
	SHA1 a;
    	a.update(to_string(i));
    	const string hash = a.final();
	unsigned long long int x=hexadecimalToDecimal(hash);
	int r=x;
	return abs(r%s);
}

int add_return(string file_path,string value)
{
	ifstream a(file_path);string basic;int line=1;
	while(!a.eof())
	{
		basic="";
		getline(a,basic);
		if(basic!="")
		{
			line++;
		}
	}
	a.close();
	
	ofstream fout(file_path,ios::app);
	fout<<value;
	fout<<endl;
	fout.close();
	return line;
}

bool check_file(string file)
{
	ifstream a(file);string basic;int count=0;
	while(!a.eof())
	{
		basic="";
		getline(a,basic);
		count++;
	}
	a.close();	
	if(count<=100)
	{
		return true;
	}
	return false;
}
