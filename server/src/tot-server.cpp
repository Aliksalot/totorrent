
#include<iostream>
#include"./scraper.h"
#include<string>

int main() {
  
  std::string html = pbscrape::getHtml("https://thepiratebay.org/index.html");

  std::cout << html << std::endl;

  return 0;
}
