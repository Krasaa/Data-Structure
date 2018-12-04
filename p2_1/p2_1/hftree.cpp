#include <string>
#include <iostream>
#include "hftree.h"
#include <fstream>
#include <cstdlib>
hfTree::hfTree(const std::string &valid_input, const double *weight, const int input_length)
{
    int length_2 = input_length;
    length = 2 * input_length;
    const double MAX_INT = 32767;
    double min1,min2;
    int x,y;
    elem = new Node[length];
    for (int i = length_2; i < length; ++i)
    {
        elem[i].weight = weight[i - length_2];
        elem[i].data = valid_input[i - length_2];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    //copy is done
    for (int i = length_2 - 1; i > 0; --i)
    {
        min1 = min2 = MAX_INT; x = y = 0;
        for (int j = i + 1;j < length; ++j)
        {
            if(elem[j].parent == 0)
            {
                if(elem[j].weight < min1)
                {
                    min2 = min1; min1 = elem[j].weight;
                    x = y;y = j;
                }
                else if(elem[j].weight < min2)
                {
                    min2 = elem[j].weight;x = j;
                }
            }
        }
        //Huffman part
        elem[i].weight = min1 + min2;
        elem[i].left = x; elem[i].right = y; elem[i].parent = 0;
        elem[x].parent = i; elem[y].parent = i;
    }
}

void hfTree::getCode(hfCode result[])
{
    int length_2 = length / 2;
    int parent, present;
    for (int i = length_2; i < length; ++i)
    {
        result[i-length_2].data = elem[i].data;
        result[i-length_2].code = "";
        parent = elem[i].parent;
        present = i;
        while(parent)
        {   //LEFT - 0 RIGHT - 1
            if (elem[parent].left == present)
            {result[i - length_2].code = '0' + result[i-length_2].code;}
            else{result[i - length_2].code = '1' + result[i-length_2].code;}
            present = parent;
            parent = elem[parent].parent;
        }
    }
}

int counting(const std::string &input, double *numbers, std::string &output)
{
    int length = input.length();
    int valid_length = 0;//nature length
    for (int iter = 0; iter < length; iter++)
    {
        for (int iter_valid = 0; iter_valid <= valid_length;iter_valid++)
        {
            if(input[iter] == output[iter_valid])
            {
                numbers[iter_valid] ++;
                break;
            }
            if(iter_valid == valid_length)
            {
                output[iter_valid] = input[iter];
                numbers[iter_valid] = 1;
                valid_length++;
                break;
            }
        }
    }
    return valid_length;
}

void initialize()
{
    char switches;
    std::string rubbish;
    std::cout<<" -------------------------------------------------------------------------- "<<std::endl;
    std::cout<<" |There are two legal operations you can choose from:                     | "<<std::endl;
    std::cout<<" |1. type 1 : Input a sequence of words, which is simple and convenient.  | "<<std::endl;
    std::cout<<" |2. type 2 : Input the characters-frequency pairs.                       | "<<std::endl;
    std::cout<<" -------------------------------------------------------------------------- "<<std::endl;

    std::cin>>switches;
    std::cin.clear();
    std::cin.ignore();

    int length_valid;
    double *numbers;
    std::string input_valid;
    if(switches == '1')
        {
        std::string input;
        std::cout<<"Please input the words :\n";
        getline(std::cin,input);
        int length = input.length();
        numbers = new double [length]{0};
        std::string input_temp(length,'*');     //bug alarm
        input_valid = input_temp;
        length_valid = counting(input, numbers, input_valid);
        //bug-free
        }
    else
    {
        if(switches == '2')
        {
            std::cout<<"Please input the number of characters :\n";
            std::cin>>length_valid;
            numbers = new double [length_valid]{0};
            std::cout<<"Please input the characters-frequency pair :\n";
            for(int iter = 0; iter < length_valid; iter++)
            {
                std::cout<<"The "<<iter+1<<" character is :"<<std::endl;
                std::cin.clear();
                std::cin.ignore();
                std::cin.get(switches);
                std::cin.clear();
                std::cin.ignore();
                std::cout<<"The "<<iter+1<<" frequency is :"<<std::endl;
                std::cin>>numbers[iter];
                input_valid = input_valid + switches;
            }
        }
        else
        {
            std::cout<<"Fatal error: Wrong input! Please rear the instruction carefully!"<<std::endl;
            return;
        }
    }
    std::ofstream write;
    write.open("hfmTree.txt",std::ios::out);
    if(!write.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    //std::cout<<"input:"<<input_valid<<"and length:"<<length_valid<<std::endl;
    //for (int i = 0; i < length_valid; i++){std::cout<<numbers[i]<<std::endl;}
    hfTree tree1(input_valid, numbers, length_valid);
    hfTree::hfCode *result = new hfTree::hfCode[length_valid];
    tree1.getCode(result);
    write<<length_valid;
/*
    for (int i = 0; i < length_valid; i++)
    {
        std::cout<<result[i].data<<" "<<result[i].code<<std::endl;
    }
*/
    //sort the output
    int store_min1 = 0;
    int flag = 0, delete_it = 0;
    write<<" ";
    for (int i = 0; i < length_valid; i++)
    {
        flag = 0;
        for (int k = 0; k < length_valid; k++)
        {
            if (result[k].code != "" && flag == 0)
            {
                store_min1 = result[k].code.length();
                flag = 1; delete_it = k;
            }
            if (result[k].code != "" && (result[k].code.length() < store_min1|| result[k].code.length() == store_min1 && result[k].code < result[delete_it].code ))
            {
                store_min1 = result[k].code.length();
                delete_it = k;
            }
        }
        write<<result[delete_it].data<<result[delete_it].code<<" ";
        result[delete_it].code = "";
    }
    write.close();
}

//get the character-code pair, used in Encoding and Decoding
void translation(const std::string &encoder, char*characters, std::string* codes, int iter_string)
{
    int length = encoder.length() - 1;
    int iter_char = 0, iter_code = -1;

    for (; iter_string < length; iter_string++)
    {
        if(encoder[iter_string] == ' ')
        {
            characters[iter_char] = encoder[iter_string + 1];
            iter_char++;
            iter_code++;
            iter_string++;
        }
        if(encoder[iter_string]>= '0' && encoder[iter_string] <= '9')
        {
            codes[iter_code] = codes[iter_code] + encoder[iter_string];
        }
    }
}

void Encoding()
{
    std::ifstream write;
    write.open("hfmTree.txt");
    if(!write.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    std::string encoder;
    getline(write, encoder);
    //std::cout<<encoder;
    //get the contents

    int iter_string = 0, valid_length = 0;
    while(encoder[iter_string]>= '0' && encoder[iter_string] <= '9')
    {
        valid_length = encoder[iter_string] - '0' + 10 * valid_length;
        iter_string += 1;
    }
    //std::cout<<"encoder"<<std::endl<<"length is :"<<valid_length<<std::endl;
    char *characters = new char[valid_length];
    std::string *codes = new std::string[valid_length];

    translation(encoder, characters, codes, iter_string);
    write.close();

    std::string target;
    write.open("plainFile.txt");
    //std::cout<<write.is_open();
    if(!write.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    getline(write, target);

    /*
    for (int i = 0; i < valid_length; i++)
    {
        std::cout<<"iter"<<i<<"  "<<characters[i]<<codes[i]<<std::endl;
    }*/
    //bug-free

    int target_length = target.length();
    std::string output = "";
    for (int i = 0; i < target_length; ++i)
    {
        for(int f = 0; f < valid_length; f++)
        {
            if(target[i] == characters[f])
            {
                output = output + codes[f];
                break;
            }
        }
    }
    std::ofstream write_wow;
    write_wow.open("codeFile.txt",std::ios::out);
    if(!write_wow.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    write_wow<<output;
    write.close();
    write_wow.close();
}

void Decoding()
{
    std::ifstream file;
    file.open("hfmTree.txt");
    if(!file.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    std::string encoder;
    getline(file, encoder);
    //std::cout<<encoder;
    file.close();
    //get the contents

    int iter_string = 0, valid_length = 0;
    while(encoder[iter_string]>= '0' && encoder[iter_string] <= '9')
    {
        valid_length = encoder[iter_string] - '0' + 10 * valid_length;
        iter_string += 1;
    }
    //std::cout<<"encoder"<<std::endl<<"length is :"<<valid_length<<std::endl;
    char *characters = new char[valid_length];
    std::string *codes = new std::string[valid_length];
    translation(encoder, characters, codes, iter_string);
    //copied from Encoding, which is hard to be encapsulated

    std::string decoded = "", detector = "";
    int start = 0, length_to_detect = 0;
    file.open("codeFile.txt");
    getline(file, decoded);
    file.close();

    std::ofstream file1;
    file1.open("textFile.txt");
    if(!file1.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    while(start != decoded.length())
    {
        for (int i = 0; i < valid_length; i++)
        {
            length_to_detect = codes[i].length();
            detector = decoded.substr(start, length_to_detect);
            if(detector == codes[i])
            {
                file1<<characters[i];
                start += length_to_detect;
            }
        }
    }
    file1.close();
}

void Printing()
{
    std::ifstream file;
    file.open("codeFile.txt");
    if(!file.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    std::string content, sub;
    getline(file, content);
    file.close();
    std::ofstream file1;
    file1.open("codePrint.txt");
    if(!file1.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    int start = 0;
    int length = content.length();
    int cycle = length/50;
    for(int i = 0; i < cycle; i++)
    {
        sub = content.substr(start, 50);
        std::cout<<sub<<std::endl;
        file1<<sub<<std::endl;
        start = start + 50;
    }
    sub = content.substr(start, length - start);
    std::cout<<sub<<std::endl;
    file1<<sub;
    file1.close();

}


void Table(int current_hierachy, std::string current_string, std::string* codes, char* characters, int numbers, int side, std::ofstream &file1)
{
    //right here!
    for (int k = 0; k < current_hierachy; k++)
        {
            std::cout<<"    ";
            file1<<"    ";
        }
    for (int k = 0; k < numbers; k++)
    {
        if(current_string == codes[k])
        {
            std::cout<<characters[k]<<std::endl;
            file1<<characters[k]<<std::endl;
            return;
        }
    }

    switch (side)
    {
    case (0):
        std::cout<<side;
        file1<<side;
        break;
    case (1):
        std::cout<<side;
        file1<<side;
        break;
    default:
        ;
    }
    std::cout<<std::endl;
    file1<<std::endl;
    //left - 0
    Table(current_hierachy + 1, current_string + '0',codes, characters, numbers, 0, file1);
    Table(current_hierachy + 1, current_string + '1',codes, characters, numbers, 1, file1);
}

void Tree()
{
    std::ifstream file;
    file.open("hfmTree.txt");
    if(!file.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    std::string encoder;
    getline(file, encoder);
    std::cout<<encoder;
    file.close();
    //get the contents

    int iter_string = 0, valid_length = 0;
    while(encoder[iter_string]>= '0' && encoder[iter_string] <= '9')
    {
        valid_length = encoder[iter_string] - '0' + 10 * valid_length;
        iter_string += 1;
    }
    //std::cout<<"encoder"<<std::endl<<"length is :"<<valid_length<<std::endl;
    char *characters = new char[valid_length];
    std::string *codes = new std::string[valid_length];
    translation(encoder, characters, codes, iter_string);


    std::ofstream file1;
    file1.open("treePrint.txt");
    if(!file1.is_open()){std::cout<<"Fatal error: Failed to open the file! Please check the txt file."; exit(1);}
    int max_length = codes[valid_length - 1].length();
    int layer = 1;
    std::cout<<"\nroot";
    file1<<"\nroot";
    Table(0, "", codes, characters, valid_length, 3, file1);
    file1.close();
}

