// header guard; prevents copy and paste of header contents
#ifndef OPTION_H
#define OPTION_H

class Option {
public:
    virtual ~Option() = default; // virtual destructor; virtual functions need virtual destructors
    virtual double payoff(double S_T) const = 0;
};

#endif