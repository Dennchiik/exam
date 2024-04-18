#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;


struct Date
{
    unsigned day;
    unsigned month;
    unsigned year;

    void Output() const {
        cout << day << "/" << month << "/" << year;
    }


    bool operator<=(const Date& obj) const {
        return (*this < obj) || (*this == obj);
    }

    bool operator>=(const Date& obj) const {
        return !(*this < obj);
    }

    bool operator<(const Date& obj) const {
        if (year < obj.year) return true;
        if (year > obj.year) return false;
        if (month < obj.month) return true;
        if (month > obj.month) return false;
        return day < obj.day;
    }
    bool operator==(const Date& obj) const {
        return (year == obj.year) && (month == obj.month) && (day == obj.day);
    }
    void Input() {
        cout << "Введите день: ";
        cin >> day;
        cout << "Ведите месяц: ";
        cin >> month;
        cout << "Введите год: ";
        cin >> year;
    }
};


bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

int diff_between_dates(Date begin_date, Date end_date);


class Spending
{
    float money;
    int category;
    Date date;

public:
    Spending() : money(0), category(0), date() {}
    Spending(float mon, int cat, const Date& d) : money(mon), category(cat), date(d) {}

    void Output() const {
        cout << "Сума: " << money << endl;
        cout << "Категория: " << category << endl;
        cout << "Дата: ";
        date.Output();
        cout << endl;
    }

    void Input() {
        cout << "Введите суму: ";
        cin >> money;

        // Вывод списка доступных категорий
        cout << "Enter category (1-8): " << endl;
        cout << "1 - Продукты" << endl;
        cout << "2 - Автотовары" << endl;
        cout << "3 - Зоотовары" << endl;
        cout << "4 - Спорттовары" << endl;
        cout << "5 - Хозтовары" << endl;
        cout << "6 - Строительные товары" << endl;
        cout << "7 - Общественное питание" << endl;
        cout << "8 - Развлечения" << endl;

        // Повторный ввод категории, пока не будет введено корректное значение
        do {
            cout << "Введите категорию(1-8): ";
            cin >> category;
            if (category < 1 || category > 8) {
                cout << "Неверная категория. Введите 1-8" << endl;
            }
        } while (category < 1 || category > 8);

        cout << "Введите дату:\n";
        date.Input();
    }

    float GetMoney() const {
        return money;
    }

    int GetCategory() const {
        return category;
    }

    bool operator<(const Spending& obj) const {
        return money < obj.money;
    }
    const Date& GetDate() const {
        return date;
    }
};


class MoneyStorage
{
protected:
    long long number;
    float totalMoney;
    multiset<Spending> spendings;
    float creditLimit;

public:
    MoneyStorage() : number(0), totalMoney(0), creditLimit(0) {}
    MoneyStorage(long long num, float credit) : number(num), totalMoney(0), creditLimit(credit) {}
    MoneyStorage(multiset<Spending>& m, long long num, float t, float credit) : spendings(m), number(num), totalMoney(t), creditLimit(credit) {}

    virtual void Output() = 0;

    void Input() {
        cout << "Введите номер карты: ";
        cin >> number;
        cout << "Введите крилитный лимит: ";
        cin >> creditLimit;
    }

    void TopUp() {
        float amount;
        cout << "Введите суму для пополнения: ";
        cin >> amount;
        totalMoney += amount;
    }

    void AddSpending() {
        Spending s;
        s.Input();
        if (totalMoney >= number) {
            spendings.insert(s);
            totalMoney -= number;
            cout << "Расход успешно добавлен" << endl;
        }
        else {
            cout << "Недостаточно средств на счету для этого расхода" << endl;
        }
    }

    long long GetNumber() const {
        return number;
    }

    multiset<Spending> GetSpendings() const {
        return spendings;
    }
};

class Card : public MoneyStorage
{
    string bankName;

public:
    Card() {}
    Card(long long num, float credit, string name) : MoneyStorage(num, credit), bankName(name) {}
    Card(multiset<Spending>& m, long long num, float t, float credit, string name) : MoneyStorage(m, num, t, credit), bankName(name) {}

    void Output() {
        cout << "Детали карты:" << endl;
        cout << "Номер: " << GetNumber() << endl;
        cout << "Название банка: " << bankName << endl;
        cout << "Кредитный лимит: " << creditLimit << endl;
        cout << "Всего средств: " << totalMoney << endl;
        cout << "Расходы:" << endl;
        for (const auto& s : spendings) {
            s.Output();
            cout << endl;
        }
    }

    void Input() {
        MoneyStorage::Input();
        cout << "Введите название банка: ";
        cin >> bankName;
    }

};

class Wallet : public MoneyStorage
{
    string walletType;

public:
    Wallet() {}

    Wallet(long long num, float credit, string type) : MoneyStorage(num, credit), walletType(type) {}

    Wallet(multiset<Spending>& m, long long num, float t, float credit, string type) : MoneyStorage(m, num, t, credit), walletType(type) {}
    void Output() {
        cout << "Детали кошелька:" << endl;
        cout << "Номер: " << GetNumber() << endl;
        cout << "Тип кошелька: " << walletType << endl;
        cout << "Кредитный лимит: " << creditLimit << endl;
        cout << "Всего средств: " << totalMoney << endl;
        cout << "Расходы:" << endl;
        for (const auto& s : spendings) {
            s.Output();
            cout << endl;
        }
    }


    void Input() {
        MoneyStorage::Input();
        cout << "Введите тип електронного кошелька: ";
        cin >> walletType;
    }
};
class FinanceManagement
{
    set<MoneyStorage*> storages;

public:
    FinanceManagement() {}
    void AddStorage(MoneyStorage* ptr) {
        storages.insert(ptr);
    }

    void DeleteStorage(int number) {
        for (auto it = storages.begin(); it != storages.end(); ++it) {
            if ((*it)->GetNumber() == number) {
                storages.erase(it);
                break;
            }
        }
    }

    void Output() {
        cout << "Хранилище денег:" << endl;
        for (const auto& storage : storages) {
            storage->Output();
        }
    }

    void TopUpStorage() {
        long long num;
        cout << "Введите номер карты для пополнения: ";
        cin >> num;
        for (const auto& storage : storages) {
            if (storage->GetNumber() == num) {
                storage->TopUp();
                return;
            }
        }
        cout << "Хранилище денег не найдено" << endl;
    }

    void AddSpendingToStorage() {
        long long num;
        cout << "Введите номер карты: ";
        cin >> num;
        for (const auto& storage : storages) {
            if (storage->GetNumber() == num) {
                storage->AddSpending();
                return;
            }
        }
        cout << "Хранилище не найдено" << endl;
    }
    void DayReport() {
        vector<Spending> day;
        Date reportDate;
        reportDate.Input();

        cout << "Дата: ";
        reportDate.Output();
        cout << endl << "----------------------------------------------" << endl;

        for (const auto& storage : storages) {
            cout << "Номер: " << storage->GetNumber() << endl;
            cout << "----------------------------------------------" << endl;

            bool found = false;
            for (const auto& spending : storage->GetSpendings()) {
                if (spending.GetDate().day == reportDate.day && spending.GetDate().month == reportDate.month && spending.GetDate().year == reportDate.year) {
                    found = true;
                    day.push_back(spending);
                }
            }

            if (!found) {
                cout << "Нет затрат" << endl;
            }

            cout << endl;
        }

        cout << "Отчет за день:" << endl;
        for (const auto& spending : day) {
            spending.Output();
            cout << endl;
        }

        ofstream outFile("day_report.bin", ios::binary);
        if (outFile.is_open()) {
            for (const auto& spending : day) {
                outFile.write((char*)&spending, sizeof(Spending));
            }
            outFile.close();
        }
        else {
            cout << "Ошибка" << endl;
        }

    }

    void WeekReport() {
        vector<Spending> week;
        Date startDate, endDate;
        cout << "Введите начальную дату (ДД ММ ГГГГ): ";
        startDate.Input();
        cout << "Введите конечную дату (ДД ММ ГГГГ): ";
        endDate.Input();

        cout << "Отчет за неделю с ";
        startDate.Output();
        cout << " по ";
        endDate.Output();
        cout << endl << "----------------------------------------------" << endl;

        for (const auto& storage : storages) {
            cout << "Номер хранилища: " << storage->GetNumber() << endl;
            cout << "----------------------------------------------" << endl;

            bool found = false;
            for (const auto& spending : storage->GetSpendings()) {
                if (spending.GetDate() >= startDate && spending.GetDate() <= endDate) {
                    found = true;
                    week.push_back(spending);
                }
            }

            if (!found) {
                cout << "Нет затрат" << endl;
            }

            cout << endl;
        }
        cout << "Отчет за неделю:" << endl;
        for (const auto& spending : week) {
            spending.Output();
            cout << endl;
        }
        ofstream outFile("week_report.bin", ios::binary);
        if (outFile.is_open()) {
            for (const auto& spending : week) {
                outFile.write((char*)&spending, sizeof(Spending));
            }
            outFile.close();
        }
        else {
            cout << "Ошибка" << endl;
        }
    }

    void MonthReport() {
        vector<Spending> month;
        Date startDate, endDate;
        cout << "Введите начальную дату (ДД ММ ГГГГ): ";
        startDate.Input();
        cout << "Введите конечную дату (ДД ММ ГГГГ): ";
        endDate.Input();

        cout << "Отчет за месяц с ";
        startDate.Output();
        cout << " по ";
        endDate.Output();
        cout << endl << "----------------------------------------------" << endl;

        for (const auto& storage : storages) {
            cout << "Номер хранилища: " << storage->GetNumber() << endl;
            cout << "----------------------------------------------" << endl;

            bool found = false;
            for (const auto& spending : storage->GetSpendings()) {
                if (spending.GetDate() >= startDate && spending.GetDate() <= endDate) {
                    found = true;
                    month.push_back(spending);
                }
            }

            if (!found) {
                cout << "Нет расходов " << endl;
            }

            cout << endl;
        }
        cout << "Отчет за месяц:" << endl;
        for (const auto& spending : month) {
            spending.Output();
            cout << endl;
        }
        ofstream outFile("month_report.bin", ios::binary);
        if (outFile.is_open()) {
            for (const auto& spending : month) {
                outFile.write((char*)&spending, sizeof(Spending));
            }
            outFile.close();
        }
        else {
            cout << "Ошибка" << endl;
        }
    }


    void RatingWeek() {}
    void RatingMonth() {}
    void RatingMonthCategory() {}
    void RatingWeekCategory() {}
};

int main()
{
    setlocale(LC_ALL, "Russian");
    MoneyStorage* stor_ptr1;  // указатель на базовый абстрактный класс "Хранилище денег"
    MoneyStorage* stor_ptr2;
    stor_ptr1 = new Card(222, 2000, "Oschadbank"); // создаём банковскую карточку
    stor_ptr2 = new Wallet(111, 1000, "Paypal");   // создаём Paypal-кошелёк

    FinanceManagement system; // создаём систему управления финансами
    system.AddStorage(stor_ptr1); // добавляем в систему "храналища денег"
    system.AddStorage(stor_ptr2);
    system.Output();
    unsigned operation;
    do
    {
        cout << "\nChoose operation\n";
        cout << "1 - Top up storage\n";  // пополнить карту или кошелёк
        cout << "2 - Add spending to storage\n";  // произвести оплату с карты или кошелька
        cout << "3 - Show storages\n";  // посмотреть состояние всех карт и кошельков, включая затраты, которые осуществлялись
        cout << "4 - Show day report\n";  // посмотреть ответ по затратам за день с записью в файл
        cout << "5 - Show week report\n";  // посмотреть ответ по затратам за неделю с записью в файл
        cout << "6 - Show month report\n";  // посмотреть ответ по затратам за день с записью в файл
        cout << "7 - Show week rating\n";  // посмотреть ТОП-3 затрат за неделю с записью в файл
        cout << "8 - Show month rating\n";  // посмотреть ТОП-3 затрат за месяц с записью в файл
        cout << "9 - Show week rating for categories\n";  // посмотреть ТОП-3 категорий за неделю с записью в файл
        cout << "10 - Show month rating for categories\n";  // посмотреть ТОП-3 категорий за месяц с записью в файл
        cout << "11 - Exit\n";
        cin >> operation;
        switch (operation)
        {
        case 1:
            system.TopUpStorage();
            break;
        case 2:
            system.AddSpendingToStorage();
            break;
        case 3:
            system.Output();
            break;
        case 4:
            system.DayReport();
            break;
        case 5:
            system.WeekReport();
            break;
        case 6:
            system.MonthReport();
            break;
        case 7:
            system.RatingWeek();
            break;
        case 8:
            system.RatingMonth();
            break;
        case 9:
            system.RatingWeekCategory();
            break;
        case 10:
            system.RatingMonthCategory();
            break;
        case 11:
            cout << "Bye!\n";
            break;
        default:
            cout << "This operation does not exist!\n";
        }
    } while (operation != 11);
}
