#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>

#include "utilities.hpp"

std::string Identify(std::vector<std::vector<int>>& data,
                     std::vector<std::string>& names,
                     std::string& dna,
                     std::vector<std::string>& strs);
bool Check(std::vector<int>& nums,
           std::vector<std::string>& strs,
           std::string& dna);
bool Check(std::string& dna, const std::string& s);
#endif