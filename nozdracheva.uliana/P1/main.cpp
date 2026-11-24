#include <iostream>
#include <stdexcept>
#include <climits>

namespace nozdracheva
{
    class ISeqProperty
    {
    public:
        void operator()(int n);
        int operator()() const;
        virtual ~ISeqProperty() = default;

    private:
        virtual void next(int n) = 0;
        virtual int result() const = 0;
    };

    class SubMaxCounter : public ISeqProperty
    {
    public:
        SubMaxCounter();

    private:
        int max1;
        int max2;
        int c;

        void next(int n) override;
        int result() const override;
    };

    int findSubMax();
}

int main()
{
    try
    {
        const int res = nozdracheva::findSubMax();
        std::cout << res << "\n";
        return 0;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    catch (const std::overflow_error& e)
    {
        std::cerr << e.what() << "\n";
        return 2;
    }
}

namespace nozdracheva
{
    void ISeqProperty::operator()(int n)
    {
        next(n);
    }

    int ISeqProperty::operator()() const
    {
        return result();
    }

    SubMaxCounter::SubMaxCounter() :
        max1(INT_MIN),
        max2(INT_MIN),
        c(0)
    {
    }

    void SubMaxCounter::next(int n)
    {
        if (c == INT_MAX)
        {
            throw std::overflow_error("Sequence is too long");
        }

        ++c;

        if (n >= max1)
        {
            max2 = max1;
            max1 = n;
        }
        else if (n > max2)
        {
            max2 = n;
        }
    }

    int SubMaxCounter::result() const
    {
        if (c < 2)
        {
            throw std::overflow_error("Sequence is too short");
        }

        return max2;
    }

    int findSubMax()
    {
        SubMaxCounter counter;
        ISeqProperty& property = counter;
        int n = 0;

        while (std::cin >> n)
        {
            if (n == 0)
            {
                break;
            }

            property(n);
        }

        if (!std::cin && !std::cin.eof())
        {
            throw std::invalid_argument("Not a number entered");
        }

        return property();
    }
}
