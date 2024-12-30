//1
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

struct Date {
    int day, month, year;

    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    // Обчислення кількості днів від даної дати до поточної
    int daysSince() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        int current_day = ltm->tm_mday;
        int current_month = ltm->tm_mon + 1;
        int current_year = ltm->tm_year + 1900;

        // Просте обчислення без врахування складних факторів (наприклад, високосні роки)
        int days_in_current_year = (current_month - 1) * 30 + current_day;  // Приблизно
        int days_in_given_year = (month - 1) * 30 + day;  // Приблизно

        return days_in_current_year - days_in_given_year;
    }
};

struct Employee {
    string fullName;
    string position;
    string phone;
    string email;
    double salary;

    Employee(string fn, string pos, string ph, string em, double sal)
        : fullName(fn), position(pos), phone(ph), email(em), salary(sal) {}
};

class Company {
public:
    string name;
    Date founded;
    string businessProfile;
    string directorName;
    int numberOfEmployees;
    string address;
    vector<Employee> employees;

    Company(string n, Date f, string bp, string dn, int ne, string addr)
        : name(n), founded(f), businessProfile(bp), directorName(dn), numberOfEmployees(ne), address(addr) {}

    // Запити:
    static vector<Company> getCompaniesByName(vector<Company>& companies, const string& searchWord) {
        vector<Company> result;
        for (auto& company : companies) {
            if (company.name.find(searchWord) != string::npos) {
                result.push_back(company);
            }
        }
        return result;
    }

    static vector<Company> getCompaniesByProfile(vector<Company>& companies, const string& profile) {
        vector<Company> result;
        for (auto& company : companies) {
            if (company.businessProfile == profile) {
                result.push_back(company);
            }
        }
        return result;
    }

    static vector<Company> getCompaniesByEmployeeCountRange(vector<Company>& companies, int minEmployees, int maxEmployees) {
        vector<Company> result;
        for (auto& company : companies) {
            if (company.numberOfEmployees >= minEmployees && company.numberOfEmployees <= maxEmployees) {
                result.push_back(company);
            }
        }
        return result;
    }

    static vector<Company> getCompaniesByCity(vector<Company>& companies, const string& city) {
        vector<Company> result;
        for (auto& company : companies) {
            if (company.address.find(city) != string::npos) {
                result.push_back(company);
            }
        }
        return result;
    }

    static vector<Company> getCompaniesByDirectorLastName(vector<Company>& companies, const string& lastName) {
        vector<Company> result;
        for (auto& company : companies) {
            stringstream ss(company.directorName);
            string last_name;
            ss >> last_name;
            if (last_name == lastName) {
                result.push_back(company);
            }
        }
        return result;
    }

    static vector<Company> getCompaniesByYearFounded(vector<Company>& companies, int days) {
        vector<Company> result;
        for (auto& company : companies) {
            if (company.founded.daysSince() > days) {
                result.push_back(company);
            }
        }
        return result;
    }
};

int main() {
    vector<Company> companies;
    companies.push_back(Company("TechFood", Date(10, 1, 2020), "IT", "John Doe", 150, "London"));
    companies.push_back(Company("MarketingPro", Date(15, 3, 2018), "Marketing", "Jane Smith", 200, "Paris"));
    companies.push_back(Company("FoodX", Date(1, 5, 2015), "Food", "James Black", 50, "New York"));

    // Додаємо працівників до фірм
    companies[0].employees.push_back(Employee("Alice Brown", "Manager", "239876", "alice@example.com", 45000));
    companies[1].employees.push_back(Employee("Bob White", "Developer", "238765", "bob@example.com", 55000));

    // Запити
    vector<Company> foodCompanies = Company::getCompaniesByName(companies, "Food");
    vector<Company> marketingCompanies = Company::getCompaniesByProfile(companies, "Marketing");
    vector<Company> largeCompanies = Company::getCompaniesByEmployeeCountRange(companies, 100, 300);
    vector<Company> londonCompanies = Company::getCompaniesByCity(companies, "London");

    cout << "Companies with 'Food' in the name:" << endl;
    for (const auto& company : foodCompanies) {
        cout << company.name << endl;
    }

    cout << "Marketing companies:" << endl;
    for (const auto& company : marketingCompanies) {
        cout << company.name << endl;
    }

    return 0;
}
//2
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

class Company {
public:
    string name;
    Date founded;
    string businessProfile;
    string directorName;
    int numberOfEmployees;
    string address;
    vector<Employee> employees;

    Company(string n, Date f, string bp, string dn, int ne, string addr)
        : name(n), founded(f), businessProfile(bp), directorName(dn), numberOfEmployees(ne), address(addr) {}

    // Методи для фільтрації
    static vector<Company> filterByName(const vector<Company>& companies, const string& word) {
        vector<Company> result;
        copy_if(companies.begin(), companies.end(), back_inserter(result), [&](const Company& c) {
            return c.name.find(word) != string::npos;
            });
        return result;
    }

    static vector<Company> filterByProfile(const vector<Company>& companies, const string& profile) {
        vector<Company> result;
        copy_if(companies.begin(), companies.end(), back_inserter(result), [&](const Company& c) {
            return c.businessProfile == profile;
            });
        return result;
    }

    static vector<Company> filterByEmployeeCountRange(const vector<Company>& companies, int min, int max) {
        vector<Company> result;
        copy_if(companies.begin(), companies.end(), back_inserter(result), [&](const Company& c) {
            return c.numberOfEmployees >= min && c.numberOfEmployees <= max;
            });
        return result;
    }

    static vector<Company> filterByCity(const vector<Company>& companies, const string& city) {
        vector<Company> result;
        copy_if(companies.begin(), companies.end(), back_inserter(result), [&](const Company& c) {
            return c.address.find(city) != string::npos;
            });
        return result;
    }

    static vector<Company> filterByDirectorLastName(const vector<Company>& companies, const string& lastName) {
        vector<Company> result;
        copy_if(companies.begin(), companies.end(), back_inserter(result), [&](const Company& c) {
            stringstream ss(c.directorName);
            string last_name;
            ss >> last_name;
            return last_name == lastName;
            });
        return result;
    }
};

int main() {
    vector<Company> companies;
    companies.push_back(Company("TechFood", Date(10, 1, 2020), "IT", "John Doe", 150, "London"));
    companies.push_back(Company("MarketingPro", Date(15, 3, 2018), "Marketing", "Jane Smith", 200, "Paris"));
    companies.push_back(Company("FoodX", Date(1, 5, 2015), "Food", "James Black", 50, "New York"));

    // Використовуємо методи для фільтрації
    vector<Company> foodCompanies = Company::filterByName(companies, "Food");
    vector<Company> marketingCompanies = Company::filterByProfile(companies, "Marketing");

    // Виведення результатів
    for (const auto& company : foodCompanies) {
        cout << company.name << endl;
    }

    return 0;
}
//3
class Employee {
public:
    string fullName;
    string position;
    string phone;
    string email;
    double salary;

    Employee(string fn, string pos, string ph, string em, double sal)
        : fullName(fn), position(pos), phone(ph), email(em), salary(sal) {}

    static vector<Employee> filterBySalary(const vector<Employee>& employees, double minSalary) {
        vector<Employee> result;
        for (const auto& employee : employees) {
            if (employee.salary > minSalary) {
                result.push_back(employee);
            }
        }
        return result;
    }
};

class Company {
public:
    string name;
    Date founded;
    string businessProfile;
    string directorName;
    int numberOfEmployees;
    string address;
    vector<Employee> employees;

    Company(string n, Date f, string bp, string dn, int ne, string addr)
        : name(n), founded(f), businessProfile(bp), directorName(dn), numberOfEmployees(ne), address(addr) {}

    void addEmployee(const Employee& emp) {
        employees.push_back(emp);
    }

    vector<Employee> getEmployeesBySalary(double salary) {
        return Employee::filterBySalary(employees, salary);
    }
};

int main() {
    Company company("TechFood", Date(10, 1, 2020), "IT", "John Doe", 150, "London");

    company.addEmployee(Employee("Alice Brown", "Manager", "239876", "alice@example.com", 45000));
    company.addEmployee(Employee("Bob White", "Developer", "238765", "bob@example.com", 55000));

    // Фільтруємо працівників за зарплатою
    vector<Employee> highPaidEmployees = company.getEmployeesBySalary(50000);

    cout << "Employees with salary > 50000:" << endl;
    for (const auto& employee : highPaidEmployees) {
        cout << employee.fullName << endl;
    }

    return 0;
}
//4
#include <iostream>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>  // Потрібна бібліотека для роботи з JSON

using json = nlohmann::json;
using namespace std;

struct Fraction {
    int numerator;
    int denominator;

    Fraction(int num, int denom) : numerator(num), denominator(denom) {}

    // Перетворення об'єкта в JSON
    json to_json() const {
        return json{ {"numerator", numerator}, {"denominator", denominator} };
    }

    // Статичний метод для десеріалізації об'єкта з JSON
    static Fraction from_json(const json& j) {
        return Fraction(j.at("numerator").get<int>(), j.at("denominator").get<int>());
    }
};

void serializeFractions(const vector<Fraction>& fractions, const string& filename) {
    json j;
    for (const auto& fraction : fractions) {
        j.push_back(fraction.to_json());
    }
    ofstream file(filename);
    file << j.dump(4);  // Дамп у форматі з відступами
    file.close();
}

vector<Fraction> deserializeFractions(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    vector<Fraction> fractions;
    for (const auto& item : j) {
        fractions.push_back(Fraction::from_json(item));
    }
    return fractions;
}

int main() {
    vector<Fraction> fractions;
    int n;
    cout << "Enter number of fractions: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int numerator, denominator;
        cout << "Enter numerator and denominator for fraction " << i + 1 << ": ";
        cin >> numerator >> denominator;
        fractions.push_back(Fraction(numerator, denominator));
    }

    // Серіалізація в JSON файл
    serializeFractions(fractions, "fractions.json");

    // Завантаження з файлу та десеріалізація
    vector<Fraction> loadedFractions = deserializeFractions("fractions.json");

    cout << "Loaded fractions:" << endl;
    for (const auto& fraction : loadedFractions) {
        cout << fraction.numerator << "/" << fraction.denominator << endl;
    }

    return 0;
}
//5
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Magazine {
    string name;
    string publisher;
    string date;
    int pages;

    json to_json() const {
        return json{ {"name", name}, {"publisher", publisher}, {"date", date}, {"pages", pages} };
    }

    static Magazine from_json(const json& j) {
        return Magazine{
            j.at("name").get<string>(),
            j.at("publisher").get<string>(),
            j.at("date").get<string>(),
            j.at("pages").get<int>()
        };
    }
};

void serializeMagazine(const Magazine& magazine, const string& filename) {
    json j = magazine.to_json();
    ofstream file(filename);
    file << j.dump(4);
    file.close();
}

Magazine deserializeMagazine(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    return Magazine::from_json(j);
}

int main() {
    Magazine magazine;

    // Введення інформації про журнал
    cout << "Enter magazine name: ";
    getline(cin, magazine.name);
    cout << "Enter publisher name: ";
    getline(cin, magazine.publisher);
    cout << "Enter publication date: ";
    getline(cin, magazine.date);
    cout << "Enter number of pages: ";
    cin >> magazine.pages;

    // Серіалізація журналу у файл
    serializeMagazine(magazine, "magazine.json");

    // Завантаження з файлу та десеріалізація
    Magazine loadedMagazine = deserializeMagazine("magazine.json");

    // Виведення інформації про журнал
    cout << "Loaded magazine info:" << endl;
    cout << "Name: " << loadedMagazine.name << endl;
    cout << "Publisher: " << loadedMagazine.publisher << endl;
    cout << "Date: " << loadedMagazine.date << endl;
    cout << "Pages: " << loadedMagazine.pages << endl;

    return 0;
}
//6
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Article {
    string title;
    int charCount;
    string summary;

    json to_json() const {
        return json{ {"title", title}, {"charCount", charCount}, {"summary", summary} };
    }

    static Article from_json(const json& j) {
        return Article{
            j.at("title").get<string>(),
            j.at("charCount").get<int>(),
            j.at("summary").get<string>()
        };
    }
};

struct Magazine {
    string name;
    string publisher;
    string date;
    int pages;
    vector<Article> articles;

    json to_json() const {
        json j;
        j["name"] = name;
        j["publisher"] = publisher;
        j["date"] = date;
        j["pages"] = pages;
        j["articles"] = json::array();
        for (const auto& article : articles) {
            j["articles"].push_back(article.to_json());
        }
        return j;
    }

    static Magazine from_json(const json& j) {
        Magazine magazine{
            j.at("name").get<string>(),
            j.at("publisher").get<string>(),
            j.at("date").get<string>(),
            j.at("pages").get<int>()
        };
        for (const auto& articleJson : j.at("articles")) {
            magazine.articles.push_back(Article::from_json(articleJson));
        }
        return magazine;
    }
};

void serializeMagazine(const Magazine& magazine, const string& filename) {
    json j = magazine.to_json();
    ofstream file(filename);
    file << j.dump(4);
    file.close();
}

Magazine deserializeMagazine(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    return Magazine::from_json(j);
}

int main() {
    Magazine magazine;

    // Введення інформації про журнал
    cout << "Enter magazine name: ";
    getline(cin, magazine.name);
    cout << "Enter publisher name: ";
    getline(cin, magazine.publisher);
    cout << "Enter publication date: ";
    getline(cin, magazine.date);
    cout << "Enter number of pages: ";
    cin >> magazine.pages;
    cin.ignore();  // Чистимо буфер після cin

    // Введення інформації про статті
    int articleCount;
    cout << "Enter number of articles: ";
    cin >> articleCount;
    cin.ignore();  // Чистимо буфер після cin

    for (int i = 0; i < articleCount; ++i) {
        string title, summary;
        int charCount;
        cout << "Enter article title: ";
        getline(cin, title);
        cout << "Enter character count: ";
        cin >> charCount;
        cin.ignore();  // Чистимо буфер після cin
        cout << "Enter article summary: ";
        getline(cin, summary);

        magazine.articles.push_back(Article{ title, charCount, summary });
    }

    // Серіалізація журналу в файл
    serializeMagazine(magazine, "magazine_with_articles.json");

    // Завантаження з файлу та десеріалізація
    Magazine loadedMagazine = deserializeMagazine("magazine_with_articles.json");

    // Виведення інформації про журнал і статті
    cout << "Loaded magazine info:" << endl;
    cout << "Name: " << loadedMagazine.name << endl;
    cout << "Publisher: " << loadedMagazine.publisher << endl;
    cout << "Date: " << loadedMagazine.date << endl;
    cout << "Pages: " << loadedMagazine.pages << endl;

    cout << "Articles:" << endl;
    for (const auto& article : loadedMagazine.articles) {
        cout << "Title: " << article.title << ", Characters: " << article.charCount << endl;
        cout << "Summary: " << article.summary << endl;
    }

    return 0;
}
//7
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Article {
    string title;
    int charCount;
    string summary;

    json to_json() const {
        return json{ {"title", title}, {"charCount", charCount}, {"summary", summary} };
    }

    static Article from_json(const json& j) {
        return Article{
            j.at("title").get<string>(),
            j.at("charCount").get<int>(),
            j.at("summary").get<string>()
        };
    }
};

struct Magazine {
    string name;
    string publisher;
    string date;
    int pages;
    vector<Article> articles;

    json to_json() const {
        json j;
        j["name"] = name;
        j["publisher"] = publisher;
        j["date"] = date;
        j["pages"] = pages;
        j["articles"] = json::array();
        for (const auto& article : articles) {
            j["articles"].push_back(article.to_json());
        }
        return j;
    }

    static Magazine from_json(const json& j) {
        Magazine magazine{
            j.at("name").get<string>(),
            j.at("publisher").get<string>(),
            j.at("date").get<string>(),
            j.at("pages").get<int>()
        };
        for (const auto& articleJson : j.at("articles")) {
            magazine.articles.push_back(Article::from_json(articleJson));
        }
        return magazine;
    }
};

void serializeMagazines(const vector<Magazine>& magazines, const string& filename) {
    json j;
    for (const auto& magazine : magazines) {
        j.push_back(magazine.to_json());
    }
    ofstream file(filename);
    file << j.dump(4);
    file.close();
}

vector<Magazine> deserializeMagazines(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    vector<Magazine> magazines;
    for (const auto& magazineJson : j) {
        magazines.push_back(Magazine::from_json(magazineJson));
    }
    return magazines;
}

int main() {
    vector<Magazine> magazines;

    // Введення журналів
    int magazineCount;
    cout << "Enter number of magazines: ";
    cin >> magazineCount;
    cin.ignore();  // Чистимо буфер після cin

    for (int i = 0; i < magazineCount; ++i) {
        Magazine magazine;

        cout << "Enter magazine name: ";
        getline(cin, magazine.name);
        cout << "Enter publisher name: ";
        getline(cin, magazine.publisher);
        cout << "Enter publication date: ";
        getline(cin, magazine.date);
        cout << "Enter number of pages: ";
        cin >> magazine.pages;
        cin.ignore();  // Чистимо буфер після cin

        // Введення статей
        int articleCount;
        cout << "Enter number of articles for " << magazine.name << ": ";
        cin >> articleCount;
        cin.ignore();  // Чистимо буфер після cin

        for (int j = 0; j < articleCount; ++j) {
            string title, summary;
            int charCount;
            cout << "Enter article title: ";
            getline(cin, title);
            cout << "Enter character count: ";
            cin >> charCount;
            cin.ignore();  // Чистимо буфер після cin
            cout << "Enter article summary: ";
            getline(cin, summary);

            magazine.articles.push_back(Article{ title, charCount, summary });
        }

        magazines.push_back(magazine);
    }

    // Серіалізація журналів в файл
    serializeMagazines(magazines, "magazines.json");

    // Завантаження з файлу та десеріалізація
    vector<Magazine> loadedMagazines = deserializeMagazines("magazines.json");

    // Виведення інформації про журнали
    cout << "Loaded magazines:" << endl;
    for (const auto& magazine : loadedMagazines) {
        cout << "Name: " << magazine.name << ", Publisher: " << magazine.publisher << endl;
        cout << "Date: " << magazine.date << ", Pages: " << magazine.pages << endl;
        cout << "Articles:" << endl;
        for (const auto& article : magazine.articles) {
            cout << "Title: " << article.title << ", Characters: " << article.charCount << endl;
            cout << "Summary: " << article.summary << endl;
        }
    }

    return 0;
}
