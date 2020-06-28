#include <iostream>
#include <stdio.h>

using namespace std;

int totr;
int totc;
int totp;
struct person{
    //personal information
    int row;
    int col;
    int rt;
    int inst;
    string name;
    string state;

    //basic condition
    bool willbeinfected=false;

    //variables below are special condition
    bool needICU=false;
    bool inICU=false;
    bool dead=false;

};

person* people;
person noncase;

//to test if the declaration is correct>>Yes!!
/*void test(){
    for(int i=0; i<totp; i++){
        cout<<people[i].name<<endl;
    }
}
*/
person is_neighbor(person curr){
    for(int i=0; i<totp; i++){
        //cout <<people[i].row<<" "<<people[i].col<<" ";
        //cout << people[i].name<<" "<<curr.name<<endl;
        if(((people[i].col==curr.col)&&(abs(people[i].row-curr.row)==1))||((people[i].row==curr.row)&&(abs(people[i].col-curr.col)==1))){
            //cout << people[i].name<<endl;
            return people[i];

        }
        
    }
    return people[totp+1];
}

/*
void healthy(){

}

void masked(){

}

void sick(person p, int time){

}*/
int main()
{
    int ICUspace;
    int testT;
    cin>>totr>>totc>>ICUspace>>testT>>totp;
    people = new person[totp+1];
    //person ICU[ICUspace];
    //people[0]= NULL;
    for(int i=0; i<totp; i++){
        cin>>people[i].inst>>people[i].row>>people[i].col>>people[i].name>>people[i].state;
    }
    /*
    for(int t=0; t<=testT; t++){
        for(int i=0; i<totp; i++){
            if(people[i].state=="Healthy"){

            }
            if(people[i].state=="Masked"){

            }
            if(people[i].state=="Sick"){

            }
        }
    }*/
    //to test if the container works>>Yes!!
    /*
    for(int i=0; i<totp; i++){
        printf("The %d th element in the container is: ",i);
        cout<<people[i].inst<<", "<<people[i].row<<", "<<people[i].col<<", "<<people[i].name<<", "<<people[i].state<<endl;
    }
    */
    for(int i=0; i<totp; i++){
        cout<<"Current person in concern is: "<<people[i].name<<endl;
        cout<<"The neighbor up to him/her is: "<<is_neighbor(people[i]).name<<endl;
        //cout<<"He/She has no up neighbor!!"<<" "<< i<<endl;

    }
    //delete[] people;
    return 0;
}
