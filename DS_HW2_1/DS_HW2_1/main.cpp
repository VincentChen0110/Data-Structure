//
//  main.cpp
//  DS_hw2
//
//  Created by Vincent on 4/20/20.
//  Copyright © 2020 Vincent. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int icu_capacity;
int t = 0;
float dead = 0;

struct Person
{
    int row, col, recovery_time;
    bool icu;
    bool DoA;
    string status, name;
    int sick_neighbours;
    int death_count;
    Person *next;
};

/*void delete()
{
    
}*/
void joinHospital(Person **root, int checkin_time, int row, int col, string name, string status)
{
    Person *temp = new Person;
    Person *head;

    temp->row = row;
    temp->col = col;
    temp->DoA = false;
    temp->name = name;
    temp->status = status;
    temp->icu = false;
    temp->sick_neighbours = 0;
    temp->death_count = 7;
    temp->next = NULL;

    if (temp->status == "Sick")
        temp->recovery_time = 14;

    if (temp->status == "Healthy")
        temp->recovery_time = -1;

    if (temp->status == "Masked")
        temp->recovery_time = 0;

    if (*root == NULL)
    {
        *root = temp;
    }
    else
    {
        head = *root;
        while (head != NULL)
        {
            if (head->DoA)
            {
                if(head->row==temp->row && head->col==temp->col)
                    delete temp;
            }
            if (!head->icu && !head->DoA)
            {
                int rdelta = abs(head->row - temp->row);
                int cdelta = abs(head->col - temp->col);
                if ((rdelta == 1 && cdelta == 0) || (rdelta == 0 && cdelta == 1))
                {
                    if (head->status == "Healthy" && temp->status == "Sick")
                    {
                        head->status = "Sick";
                        head->recovery_time = 14 + 7;
                        head->sick_neighbours += 1;
                        temp->sick_neighbours += 1;
                    }
                    else if (head->status == "Sick" && temp->status == "Sick")
                    {
                        head->recovery_time += 7;
                        temp->recovery_time += 7;
                        temp->sick_neighbours += 1;
                        head->sick_neighbours += 1;
                    }
                    else if (head->status == "Sick" && temp->status == "Healthy")
                    {
                        temp->status = "Sick";
                        temp->recovery_time = 14 + 7;
                        temp->sick_neighbours += 1;
                        head->sick_neighbours += 1;
                    }
                }
            }

            // move to next person
            if (head->next == NULL)
            {
                head->next = temp;
                break;
            }
            else
                head = head->next;
        }
    }
}
void status_check(Person *root, int t)
{
    Person *current = root;
    cout << "-- statuscheck " << t << " --" << endl;
    while (current != NULL)
    {
        cout << current->row << " " << current->col << " " << current->name << " " << current->recovery_time << " " << current->status << " " << current->death_count << " " << current->sick_neighbours << " " << current->icu << " " << current->DoA << endl;
        current = current->next;
    }
    cout << "-- statuscheck end --" << endl;
}
void status_update(Person *root)
{
    Person *current = root;
    while (current != NULL)
    {
        if (!current->DoA && !current->icu)
        {

            if (current->recovery_time > 28)
            {
                if (icu_capacity > 0)
                {
                    current->icu = true;
                    icu_capacity--;
                }
            }

            if (!current->icu && current->status == "Sick")
            {
                current->recovery_time -= 1;
                if (current->recovery_time == 0)
                    current->status = "Healthy";// sickneighbors need to minus 1
            }
  
            if (!current->icu && current->sick_neighbours > 3)
            {
                current->death_count--;
                if (current->death_count == 0)
                {
                    dead++;
                    current->DoA = true;
                }
            }
        }

        current = current->next;
    }
}
void print_survive(Person *root, int max_rows, int max_cols)
{

    // Person *matrixPerson[max_rows][max_cols];

    int i, j;

    Person **matrixPerson = new Person *[max_rows * max_cols];

    for (i = 0; i < max_rows; i++)
    {
        for (j = 0; j < max_cols; j++)
        {
            matrixPerson[max_cols * i + j] = NULL;
        }
    }
    Person *trav = root;
    while (trav != NULL)
    {
        matrixPerson[max_cols * trav->row + trav->col] = trav;
        trav = trav->next;
    }
    bool flag = true;
    for (int i = 0; i < max_rows; i++)
    {
        for (int j = 0; j < max_cols; j++)
        {
            if (matrixPerson[max_cols * i + j] != NULL)
            {
                Person *current = matrixPerson[max_cols * i + j];
                if (current->DoA == false && current->icu == false)
                {
                    if (flag)
                    {
                        cout << current->name;
                        flag = false;
                    }
                    else
                        cout << " " << current->name;
                }
            }
        }
    }
}

int main()
{
    int max_rows, max_cols, output_time;
    cin >> max_rows >> max_cols >> icu_capacity >> output_time;
    //cout << max_rows << " " << max_cols << " " << icu_capacity << " " << output_time << endl;
    int number_of_persons;
    cin >> number_of_persons;
    float n1 = number_of_persons;
    Person *root = NULL;
    while (number_of_persons--)
    {
        int checkin_time, row, col;
        string name, status;
        cin >> checkin_time >> row >> col >> name >> status;
        while (t != checkin_time) //while time goes, recovery status change
        {
            status_update(root);
            //status_check(root, t);
            t++;
        }
        //cout << "joinHospital " << name << endl;
        joinHospital(&root, checkin_time, row, col, name, status);
        //status_check(root, t);
    }
    //cout << "finished inputting people, t=" << t << endl;
    while (t != output_time+1) //if last input in but output_time not yet
    {
        //cout << "status update, t=" << t << endl;
        status_update(root);
        //status_check(root, t);
        t++;
    }
    float death_rate = ((n1 - dead) / n1) * 100;
    printf("%.2f%s\n", death_rate, "%");
    //cout <<setprecision(2)<<death_rate<<"%";
    print_survive(root, max_rows, max_cols);
}
