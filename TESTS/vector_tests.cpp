#include<iostream>
#include "../ft_containers.hpp"
#include <map>
#include <random>
#include <vector>


int main()
{
    std::cout << "TESTING" << std::endl << std::endl;
    {
        std::vector<int> v;
        ft::Vector<int> ft_v;



        for(size_t i=0; i < 5; i++)
        {
            v.push_back(i);
            ft_v.push_back(i);
        }
        // v.pop_back();
        // ft_v.pop_back();
        std::vector<int>::iterator v_it = v.begin();
        ft::Vector<int>::iterator ft_vit = ft_v.begin();

       
        
        for(size_t i=0; i < v.size(); i++)
        {
            std::cout << "V " << *v_it << " ||| "<< "FT_V " << *ft_vit << std::endl;
            //std::cout << "FT_V " << *ft_vit << std::endl;

            v_it++;
            ft_vit++;
        }
        std::cout << std::endl;        
    }

    {
        std::vector<int> v;
        ft::Vector<int> ft_v;

        for(size_t i=0; i < 5; i++)
        {
            v.push_back(i);
            ft_v.push_back(i);
        }
        std::vector<int>::iterator v_it = v.begin();
        std::vector<int>::const_iterator cv_it = v.begin();

        ft::Vector<int>::iterator ft_vit = ft_v.begin();
        ft::Vector<int>::const_iterator cft_vit = ft_v.begin();

        if (v_it == cv_it && ft_vit == cft_vit)
            std::cout << "Comparaison between Iterators and const iterators" << std::endl << std::endl;
        
        std::cout << "Vectors size before inserting a new element "  << std::endl << std::endl;
        std::cout <<    "V SIZE: "       << v.size() << " ||| " << "FT_V SIZE : "       << ft_v.size()    << std::endl; 
        std::cout << std::endl;  
        v.push_back(10);
        ft_v.push_back(10);

        std::cout << "Vectors size after inserting a new element "  << std::endl << std::endl; 

        std::cout <<    "V SIZE: "       << v.size() << " ||| " << "FT_V SIZE : "       << ft_v.size()    << std::endl; 
       //std::cout << "My Vector Size : "       << ft_v.size()      << std::endl<< std::endl;
        std::cout << std::endl;      
    }

    {
        std::vector<int> v;
        ft::Vector<int> ft_v;
        std::vector<int> v2;
        ft::Vector<int> ft_v2;

        for(size_t i=0; i < 5; i++)
        {
            v.push_back(i);
            ft_v.push_back(i);
        }
        for(size_t i=10; i < 15; i++)
        {
            v2.push_back(i);
            ft_v2.push_back(i);
        }

        std::vector<int>::iterator v_it = v.begin();
        std::vector<int>::iterator v_it2 = v2.begin();

        ft::Vector<int>::iterator ft_vit = ft_v.begin();
        ft::Vector<int>::iterator ft_vit2 = ft_v2.begin();

        std::cout << "BEFORE SWAPPING VECTORS" << std::endl << std::endl;

        for(size_t i=0; i < v.size(); i++)
        {
            std::cout << "V " << *v_it << " | " << "V2 " << *v_it2 << " ||| " << "FT_V " << *ft_vit << " | " << "FT_V2 " << *ft_vit2<< std::endl;

            v_it++;
            ft_vit++;
            v_it2++;
            ft_vit2++;
        }
        std::cout << std::endl;

        //Swap
        v.swap(v2);
        ft_v.swap(ft_v2);

        v_it = v.begin();
        ft_vit = ft_v.begin();
        v_it2 = v2.begin();
        ft_vit2 = ft_v2.begin();

        std::cout << "AFTER SWAPPING VECTORS" << std::endl << std::endl;

        for(size_t i=0; i < v.size(); i++)
        {
            std::cout << "V " << *v_it << " | " << "V2 " << *v_it2 << " ||| " << "FT_V " << *ft_vit << " | " << "FT_V2 " << *ft_vit2<< std::endl;

            v_it++;
            ft_vit++;
            v_it2++;
            ft_vit2++;
        }

        std::cout << std::endl;
    }

    {
        std::vector<int> v;
        ft::Vector<int> ft_v;



        for(size_t i=0; i < 5; i++)
        {
            v.push_back(i);
            ft_v.push_back(i);
        }

        std::vector<int>::iterator v_it2;
        ft::Vector<int>::iterator  ft_vit2;


        v.pop_back();
        ft_v.pop_back();
        v_it2 = v.end();
        ft_vit2 = ft_v.end();

        std::cout << "after pop back" << std::endl << std::endl;
        std::cout << *v_it2 << " | " << *ft_vit2 << std::endl << std::endl;

        v_it2 = v.begin();
        ft_vit2 = ft_v.begin();

        v_it2++;
        ft_vit2++;
        std::cout << "second element before erease" << std::endl << std::endl;
        std::cout << *v_it2 << " | " << *ft_vit2 << std::endl<< std::endl;

        v.erase(v_it2);
        ft_v.erase(ft_vit2);
        std::vector<int>::iterator v_it = v.begin();
        ft::Vector<int>::iterator ft_vit = ft_v.begin();

        std::cout << "all remaing elemenst" << std::endl << std::endl;
        for(size_t i=0; v_it != v.end(); i++)
        {
            std::cout << "V " << *v_it  << " ||| " << "FT_V " << *ft_vit  << std::endl;

            v_it++;
            ft_vit++;
        }
    }
    //system("leaks vector.out");
}