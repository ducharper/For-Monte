#ifndef FOR_MONTE_OPTION_H
#define FOR_MONTE_OPTION_H

enum class OptionType { Call, Put };

class Option {
public:
    Option(double strikePrice, double maturity)
        : strikePrice(strikePrice), maturity(maturity) {}

    virtual ~Option() = default;

    virtual double payoff(double spotPriceAtMaturity) const = 0;
    virtual OptionType getType() const = 0;

    double getStrikePrice() const { return strikePrice; }
    double getMaturity() const { return maturity; }

protected:
    double strikePrice;
    double maturity;
};

#endif //FOR_MONTE_OPTION_H