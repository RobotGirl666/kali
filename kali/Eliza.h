/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Eliza.h
 * Author: vangelis
 *
 * Created on 4 September 2020, 10:38 am
 */

#ifndef ELIZA_H
#define ELIZA_H

#include <string>
#include <vector>
#include <boost/regex.hpp>

namespace MB
{

struct exchange
{
    boost::regex prompt_;
    std::vector<std::string> responses_;
    explicit exchange(const std::string& prompt)
      : prompt_(prompt, boost::regex::icase)
    {
    }
};
 
class exchange_builder;

class Eliza {
    std::string name_;
    std::vector<exchange> exchanges_;
    std::vector<std::pair<std::string, std::string> > translations_;
public:
    Eliza(const std::string& name = "Kali")
      : name_(name)
    {
        add_translations();
        add_responses();
    }

    const std::string& name() const
    {
        return name_;
    }

    void converse();
    exchange_builder responds_to(const std::string& prompt);
    void add_exchange(const exchange& ex)
    {
        exchanges_.push_back(ex);
    }
    std::string respond(const std::string& input) const;
    void add_responses();
private:
    void add_translations();
    std::string translate(const std::string& input) const;
};

class exchange_builder
{
    friend Eliza;
    Eliza& eliza_;
    exchange exchange_;
 
    exchange_builder(Eliza& el, const std::string& prompt)
      : eliza_(el), exchange_(prompt)
    {
    }
 
public:
    ~exchange_builder()
    {
        eliza_.add_exchange(exchange_);
    }
 
    exchange_builder& with(const std::string& response)
    {
        exchange_.responses_.push_back(response);
        return *this;
    }
};

}; // namespace MB

#endif /* ELIZA_H */

