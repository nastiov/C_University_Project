/* Индивидуальный проект. Овчинко А.В. Программа для логистических расчетов объема и веса груза, с предпочтением выбора транспорта.
Для нового пользователя предполагается только расчет первого заказа.
А для уже зарегистрировавшихся пользователей, так же существует возможность вывода отчетов:
1. Расчитать новый заказ.
2. История поиска авто.
3. История заказов по объему.
4. Статистика эффективности заполняемости авто.
5. Статистика стоимости перевозки к объему.
*/
#include <iostream> //Бибилиотека для организации ввода-вывода
#include <fstream> // Библиотека для чтения-записи данных из-в файл.
#include <iomanip> // Бибилиотека манипуляторов для потоков ввода/вывода

using namespace std; //Объявление пространства std (сообщает компилятору, что мы используем все объекты из пространства имен std!)

//Структура для отчетов клиентов
struct client {
    int number; //Порядковый номер операции в системе (1)
    char name[20]; //Имя пользователя (2)
    double order; //Номер заказа пользователя (3)
    short Kef; //Эффективность заполнения авто (4)
    char city[25]; //Город доставки (5)
    short way_days; //Кол-во дней доставки (6)
};

//Структура для отчетов заказов
struct order {
    char name[20]; //Имя пользователя (1)
    double order; //Номер заказа пользователя (2)
    double day_month; //Дата заказа (3)
    double volume; //Объем заказа (4)
    double price; //Ставка авто (5)
    char avto[25]; //Вид траспорта (6) 
};

// Прототипы функций
double RazmerKorobki(double Dlina, double Shirina, double Visota); // Объем коробки
double VolumeGoods(double Dlina, double Shirina, double Visota, double Quantity); // Объем груза с паллетами
double WeightGoods(double Dlina, double Shirina, double Visota, double Quantity, double Weight); // Вес всего груза с паллетами
void car(double RezultVolumeGoods, double RezultWeightGoods); // Выбор авто для перевозки с использованием операторов if
void output_dataclient(client* arrc, char* user_my_pr); // Функция для 2. История поиска авто.
void output_dataorder(order* arro, char* user_my_pr); // Функция для 3. История заказов по объему.
void output_reportvolume(client* arrc, char* user_my_pr); // Функция для 4. Статистика эффективности заполняемости авто.
void output_reportcost(client* arrc, order* arro, char* user_my_pr); // Функция для 5. Статистика стоимости перевозки к объему.

// Основная часть программы
int main()
{
    setlocale(LC_ALL, "Russian"); // Подключение кириллицы

    /* Программа предполагает авторизацию трех ранее записанных пользователей и
        запрос на регистрацию нового пользоваеля, где имя вносится латиницей*/
    char user_my_pr[7]; // Сохранение имени пользователя при авторизации на входе 
    char answer; //Ответ на необходимость регистрации
    string user_new; //Имя нового пользователя
    int pass_new; //Пароль нового пользователя
    int user1 = 1111, user2 = 2222, user3 = 3333, pass; //Данные имеющихся в базе пользователей
    int m = 1;//ограничение перехода по метке

   /* int mass[3][4];
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j< 5; j++)
        {
            if (i == 1) {
                mass[i][j] = 1;
                cout << mass[i][j];
            }
            else if (i == 2) {
                mass[i][j] = 2;
                cout << mass[i][j];
            }
            else
            {
                mass[i][j] = 3;
                cout << mass[i][j];
            }

        }
    } */

    cout << "Добрый день! Вы вошли в систему расчета объема и веса груза для поиска оптимального транспорта." << endl;
    cout << "Были ли Вы ранее зарегистрированы или же нуждаетесь в регистрации?" << endl;
    cout << "Для авторизации имеющигося профиля введите - 'Y' " << endl;
    cout << "Для регистрации нового пользователя введите - 'N' " << endl;
    cin >> answer;

    // Включение метки М необходимо для разрешения сценария при неправильно вводе пароля три раза.
M:
    /*  В данном меню использована структура цикла if, так как в случае неверного ввода пароля
        предполагается несколько сценариев: 1. правильный ввод пароля и переход ко второму меню,
        2. неверный ввод пароля и возможность ввести его ещё раз, 3. стоит счетчик на три попытки.*/

    if ((answer == 'Y') || (answer == 'y')) {
        cout << "Введите Ваш индефикационный номер: ";
        cin >> pass;
        if (pass == user1) {
            cout << "Вы вошли под именем: Пользователь №1." << endl;
            strcpy_s(user_my_pr, "user1"); // Запись логина пользователя №1
        }
        else if (pass == user2)
        {
            cout << "Вы вошли под именем: Пользователь №2." << endl;
            strcpy_s(user_my_pr, "user2"); // Запись логина пользователя №2
        }
        else if (pass == user3) {
            cout << "Вы вошли под именем: Пользователь №3." << endl;
            strcpy_s(user_my_pr, "user3"); // Запись логина пользователя №3
        }
        else
        {
            cout << "Вами был введен неверный номер." << endl;
            if (m < 3) // Счетчик на ввод 3-х попыток ввода пароля
            {
                m++;
                goto M;
            }
            else
            {
                cout << "Ошибка!" << endl;
                system("pause");
                return 0;
            }
        }
    }
    else if ((answer == 'n') || (answer == 'N')) {
        cout << "Для регистрации введите имя пользователя (*латинские символы): ";
        cin >> user_new; //Сохранение логина нового пользователя
        cout << endl << "Пароль для входа в профиль:";
        cin >> pass_new; // Сохранение пароля нового пользователя 
        cout << endl;
        cout << "Поздравляем, " << user_new << " регистрация прошла успешно. Ваш пароль для входа: " << pass_new << endl;
    }
    else {
        cout << "Ошибка!" << endl;
        system("pause");
        return 0;
    }

    // Подключение структур и считывание файлов
    client arrc[16];
    order arro[16];
    ifstream dataclient;
    ifstream dataorder;

    dataclient.open("E://DATAclient.txt");
    if (!dataclient.is_open())
    {
        cout << "Файл не может быть открыт." << endl;
    }
    else {
        for (int i = 0; i < 16; i++)
        {
            dataclient >> arrc[i].number; //Порядковый номер операции в системе (1)
            dataclient >> arrc[i].name; //Имя пользователя (2)
            dataclient >> arrc[i].order; //Номер заказа пользователя (3)
            dataclient >> arrc[i].Kef; //Эффективность заполнения авто (4)
            dataclient >> arrc[i].city; //Город доставки (5)
            dataclient >> arrc[i].way_days;//Кол-во дней доставки (6)
        }
    }
    dataorder.open("E://DATAorder.txt");
    if (!dataorder.is_open())
    {
        cout << "Файл не может быть открыт." << endl;
    }
    else {
        for (int i = 0; i < 16; i++)
        {
            dataorder >> arro[i].name; //Имя пользователя (1)
            dataorder >> arro[i].order; //Номер заказа пользователя (2)
            dataorder >> arro[i].day_month; //Дата заказа (3)
            dataorder >> arro[i].volume; //Объем заказа (4)
            dataorder >> arro[i].price; //Ставка авто (5)
            dataorder >> arro[i].avto; //Вид траспорта (6) 
        }
    }


    int menu; // Переменная для ввода пункта меню
    char answer2; // Переменная для ввода ответа после отчетов

    do {
        cout << " " << "Меню выбора: " << endl;
        cout << " " << "1. - Расчитать новый заказ." << endl;
        cout << " " << "2. - История поиска авто." << endl;
        cout << " " << "3. - История заказов по объему." << endl;
        cout << " " << "4. - Статистика эффективности заполняемости авто." << endl;
        cout << " " << "5. - Статистика стоимости перевозки к объему." << endl;
        cout << " " << "6. - Завершить работу программы. " << endl;
        cout << endl;
        cout << " " << "Выберите нужный пункт меню: ";
        cout << endl;
        cin >> menu;
        switch (menu)
        {
        case 1: // Расчитать новый заказ.
            cout << endl;
            cout << "Для расчета введите необходимые данные, придерживайтесь инструкций." << endl;
            cout << endl;

            //Объявление переменных для расчета объема груза
            int Dlina; // Длина коробки
            int Shirina; // Ширина коробки
            int Visota; // Высота коробки
            double RezultRazmerKorobki; // Результат размера коробки
            double RezultVolumeGoods; // Результат объема всего груза
            double RezultWeightGoods; // Результат веса всего груза
            int Quantity; // Количество коробок
            double Weight; // Вес одной коробки

            // Инициализация переменных для расчета объема груза
            cout << "Введите длину коробки (см): ";
            cin >> Dlina;
            cout << "Введите ширину коробки (см): ";
            cin >> Shirina;
            cout << "Введите высоту коробки (см): ";
            cin >> Visota;

            //Расчет размера коробки
            RezultRazmerKorobki = RazmerKorobki(Dlina, Shirina, Visota);
            cout << "Размер коробки равен (м3): " << RezultRazmerKorobki << endl;

            //Расчет объема груза
            cout << "Введите количество коробок: ";
            cin >> Quantity;
            RezultVolumeGoods = VolumeGoods(Dlina, Shirina, Visota, Quantity);
            cout << "Объем груза (м3): " << RezultVolumeGoods << endl;

            //Расчет веса груза
            cout << "Введите примерный вес одной коробки (кг): ";
            cin >> Weight;
            RezultWeightGoods = WeightGoods(Dlina, Shirina, Visota, Quantity, Weight);
            cout << "Общий вес груза (т.): " << RezultWeightGoods << endl;

            //Выбор авто для перевозки с использованием операторов if
            car(RezultVolumeGoods, RezultWeightGoods);

            cout << endl;
            break;

        case 2: // История поиска авто.
            if ((answer == 'Y') || (answer == 'y')) {
                output_dataclient(arrc, user_my_pr);
                cout << endl;
            }
            else {
                cout << "У вас нет доступа к этому разделу." << endl;
            }
            cout << endl;
            break;

        case 3: // История заказов по объему.
            if ((answer == 'Y') || (answer == 'y')) {
                output_dataorder(arro, user_my_pr);
                cout << endl;
            }
            else {
                cout << "У вас нет доступа к этому разделу." << endl;
            }
            cout << endl;
            break;

        case 4: // Статистика эффективности заполняемости авто.
            if ((answer == 'Y') || (answer == 'y')) {
                output_reportvolume(arrc, user_my_pr);
            }
            else {
                cout << "У вас нет доступа к этому разделу." << endl;
            }
            cout << endl;
            break;

        case 5: // Статистика стоимости перевозки к объему.
            if ((answer == 'Y') || (answer == 'y')) {
                output_reportcost(arrc, arro, user_my_pr);
            }
            else {
                cout << "У вас нет доступа к этому разделу." << endl;
            }
            cout << endl;
            break;

        case 6: // Завершить работу программы.
            exit(0);
        default:
            break;
        }
        cout << endl;
        cout << " " << "Желаете вернуться в меню выбора? Y/N ";
        cin >> answer2;
        if ((answer2 != 'Y') && (answer2 != 'y'))
        {
            cout << endl;
            cout << " " << "Работа программы завершена.";
            cout << endl;
            system("pause");
            return 0;
        }
    } while (1 > 0);
}

//Определение функций

//Функция расчета объема коробки
double RazmerKorobki(double Dlina, double Shirina, double Visota)
{
    return (Dlina * Shirina * Visota) / 1000000;
}

/*Функция расчета объема всего товара для погрузки, при этом учитывается объем усиленной евро паллеты */
double VolumeGoods(double Dlina, double Shirina, double Visota, double Quantity)
{
    return ((((Dlina * Shirina * Visota) / 1000000 + 0.001) * Quantity) + (0.144 * (Quantity / ((120 * 80 * 155) / (Shirina * Dlina * Visota)))));
}

/* Функция расчета веса всего товара в тоннах для погрузки, при этом учитывается вес усиленной евро паллеты с высотой загрузки 1,55 м */
double WeightGoods(double Dlina, double Shirina, double Visota, double Quantity, double Weight)
{
    return ((Quantity * Weight / 1000) + (0.015 * (Quantity / ((120 * 80 * 155) / (Shirina * Dlina * Visota)))));
}

// Функция для 2. История поиска авто.
void output_dataclient(client* arrc, char* user_my_pr)
{
    cout << setw(10) << "№";
    cout << setw(20) << "Пользователь";
    cout << setw(10) << "Заказ";
    cout << setw(20) << "Заполнение авто %";
    cout << setw(25) << "Город";
    cout << setw(15) << "Дней в пути";
    cout << endl;
    for (int i = 0; i < 16; i++)
    {
        if (!strcmp(arrc[i].name, user_my_pr))
        {
            cout << setw(10) << arrc[i].number;
            cout << setw(20) << arrc[i].name;
            cout << setw(10) << arrc[i].order;
            cout << setw(20) << arrc[i].Kef;
            cout << setw(25) << arrc[i].city;
            cout << setw(15) << arrc[i].way_days;
            cout << endl;
        }
    }
}

// Функция для 3. История заказов по объему.
void output_dataorder(order* arro, char* user_my_pr)
{
    cout << setw(10) << "Пользователь";
    cout << setw(20) << "Заказ";
    cout << setw(10) << "Дата";
    cout << setw(10) << "Объем";
    cout << setw(20) << "Ставка";
    cout << setw(25) << "Транспорт";
    cout << endl;
    for (int i = 0; i < 16; i++)
    {
        if (!strcmp(arro[i].name, user_my_pr))
        {
            cout << setw(10) << arro[i].name;
            cout << setw(20) << arro[i].order;
            cout << setw(10) << arro[i].day_month;
            cout << setw(10) << arro[i].volume;
            cout << setw(20) << arro[i].price;
            cout << setw(25) << arro[i].avto;
            cout << endl;
        }
    }
}

// Функция для 4. Статистика эффективности заполняемости авто.
void output_reportvolume(client* arrc, char* user_my_pr)
{
    short number_of_way = 0;
    cout << setw(5) << "№";
    cout << setw(15) << "Пользователь";
    cout << setw(7) << "Заказ";
    cout << setw(5) << "Кэф";
    cout << setw(15) << "Город";
    cout << setw(15) << "Дней в пути";
    cout << endl;
    for (int i = 0; i < 16; i++)
    {
        if (arrc[i].Kef >= 80)
        {
            if (!strcmp(arrc[i].name, user_my_pr))
            {
                cout << setw(5) << arrc[i].number;
                cout << setw(15) << arrc[i].name;
                cout << setw(7) << arrc[i].order;
                cout << setw(5) << arrc[i].Kef;
                cout << setw(15) << arrc[i].city;
                cout << setw(15) << arrc[i].way_days;
                cout << endl;
                number_of_way += 1;
            }
        }
    }
    cout << "Всего " << number_of_way << " эффективно сформированных заказов авто." << endl;
}

// Функция для 5. Статистика стоимости перевозки к объему.
void output_reportcost(client* arrc, order* arro, char* user_my_pr)
{
    cout << setw(15) << "Пользователь";
    cout << setw(15) << "№";
    cout << setw(15) << "Цена за ед.";
    cout << setw(15) << "Город";
    cout << setw(5) << "Кэф";
    cout << endl;

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (arrc[i].order == arro[j].order)
                if (!strcmp(arrc[i].name, user_my_pr))
                {
                    cout << setw(15) << arro[j].name;
                    cout << setw(15) << arrc[i].order;
                    cout << setw(15) << ((arro[j].price / arro[j].volume) / arrc[i].way_days);
                    cout << setw(15) << arrc[i].city;
                    cout << setw(5) << arrc[i].Kef;
                    cout << endl;
                    i++;
                }
        }
    }
}

// Функция для 1. Выбор авто для перевозки с использованием операторов if
void car(double RezultVolumeGoods, double RezultWeightGoods)
{

    if (RezultVolumeGoods <= 6) {
        if (RezultWeightGoods <= 1) {
            cout << "Для перевозки предпочтителен 'Портер' (до 6м3-1т-4паллеты)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 6) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 6 && RezultVolumeGoods <= 9) {
        if (RezultWeightGoods <= 1.5) {
            cout << "Для перевозки предпочтителена 'Газель' (до 9м3-1,5т-4паллеты)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 9) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 9 && RezultVolumeGoods <= 15) {
        if (RezultWeightGoods <= 11) {
            cout << "Для перевозки предпочтителен 'Контейнер 10''DC (до 15м3-11т-5паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 15) << " % от контейнера.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 15 && RezultVolumeGoods <= 20) {
        if (RezultWeightGoods <= 5) {
            cout << "Для перевозки предпочтителен 'ЗИЛ' (до 20м3-5т-12паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 20) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 20 && RezultVolumeGoods <= 30) {
        if (RezultWeightGoods <= 10) {
            cout << "Для перевозки предпочтителен 'МАЗ' (до 30м3-10т-15паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 30) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 30 && RezultVolumeGoods <= 32) {
        if (RezultWeightGoods <= 22) {
            cout << "Для перевозки предпочтителен 'Контейнер 20' (до 32м3-22т-9паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 32) << " % от контейнера.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 33 && RezultVolumeGoods <= 65.6) {
        if (RezultWeightGoods <= 27) {
            cout << "Для перевозки предпочтителен 'Контейнер 40' (до 65.5м3-27т-21паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 65.5) << " % от контейнера.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 65.5 && RezultVolumeGoods <= 82) {
        if (RezultWeightGoods <= 20) {
            cout << "Для перевозки предпочтителен 'Фура евро82' (до 82м3-20т-30паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 82) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 82 && RezultVolumeGoods <= 90) {
        if (RezultWeightGoods <= 22) {
            cout << "Для перевозки предпочтителен 'Еврофура' (до 90м3-22т-33паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 90) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else if (RezultVolumeGoods > 90 && RezultVolumeGoods <= 120) {
        if (RezultWeightGoods <= 22) {
            cout << "Для перевозки предпочтительна 'Сцепка Mega' (до 120м3-22т-36паллет)." << endl;
            cout << "При этом заполняемость: " << static_cast<int>(RezultVolumeGoods * 100 / 120) << " % от авто.";
        }
        else {
            cout << "Стоит рассмотреть авто с большими габаритами, так как груз нестандартный.";
        }
    }
    else {
        cout << "Стоит рассмотреть разбивку на несколько партий, так как груз нестандартный.";
    }

}