## The Problem

You work as a developer at **LinkedOut**, a platform that connects companies with professionals. 


LinkedOut operates a website for both professionals and companies to register and seek for jobs and candidates, respectively.


The basic goal of LinkedOut is to match professionals to companies so that both parts will be happy.


### How professionals and companies choose each other?
1. Each professional compiles a **wish list** that is a rank-ordered list of companies that she/he wishes to work for.
2. Every company compiles a similar list of professionals. Moreover, each company provides the number of its currently open positions (**slots**) that wishes to fill.

## Goal

Your project is to develop an algorithm that will match professionals to companies so that the final result is very close to an **ideal hiring**.

## More Details
Assume that every company list includes every single professional and every professional ranks all the companies in the platform.


## Example

#### input_companies 
  Description: company_slots, name_of_company: comma separated list of professionals in order of most to least preferable
Sample:
```
1, Microsoft: Bill, Jeff, Mark, Larry
1, Amazon: Bill, Jeff, Mark, Larry
1, Facebook: Mark, Jeff, Bill, Larry
1, Oracle: Bill, Mark, Jeff, Larry
```

#### input_professionals 
	Description: name_of_professional: comma separated list of companies in order of most to least preferable

Sample:
```
Bill: Microsoft, Facebook, Oracle, Amazon
Jeff: Amazon, Oracle, Microsoft, Facebook
Mark: Facebook, Oracle, Microsoft, Amazon
Larry: Amazon, Oracle, Microsoft, Facebook
```


#### output_file
	Description: name of company: comma separated list of employes


Sample:
```
Microsoft: Bill
Amazon: Jeff
Oracle: Larry
Facebook: Mark
```
