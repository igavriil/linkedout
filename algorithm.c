#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"

algorithm *algorithm_new(companies_map *companies_map, professionals_map *professionals_map, companies_pool *companies_pool, professionals_pool *professionals_pool)
{
    algorithm *this = malloc(sizeof(algorithm));

    this->companies_map = companies_map;
    this->professionals_map = professionals_map;
    this->companies_pool = companies_pool;
    this->professionals_pool = professionals_pool;
    return this;
}

static inline unsigned int company_over_subscribed(const company* company)
{
    return (company->applications_count > company->capacity);
}

static inline unsigned int company_fully_subscribed(const company *company)
{
    return (company->applications_count == company->capacity);
}


static inline unsigned int professional_prefered_company(professional *professional)
{
    return queue_dequeue(professional->preferences);
}

void algorithm_run(algorithm *alg)
{
    professional (*prof);
    company (*comp);
    professional (**professionals);
    company (**companies);

    companies = alg->companies_pool->companies;
    professionals = alg->professionals_pool->professionals_array;

    while(!circular_array_empty(alg->professionals_pool->professionals))
    {
        prof = circular_array_get(alg->professionals_pool->professionals);
    	comp = companies[professional_prefered_company(prof)];
    	while (company_fully_subscribed(comp) && (comp->applications->entries[0]->priority < comp->positions[prof->identifier]))
        {
            comp = companies[professional_prefered_company(prof)];
        }

        priority_queue_insert(comp->applications, prof->identifier, comp->positions[prof->identifier]);
        comp->applications_count++;


       	if (company_over_subscribed(comp))
        {
            prof = professionals[priority_queue_delmax(comp->applications)];
            circular_array_put(alg->professionals_pool->professionals, prof);
            comp->applications_count--;
        }
    }
}
