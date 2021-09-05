#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>

using namespace std;
typedef struct Address
{
    string quartier;
    string street;
    string hourTheCommandStart;
    string hourTheCommandEnd;
    int number;
} Address;

typedef struct Order
{
    int orderIdNo;
    string clientOrEseName;
    string orderType;
    int flourId;
    Address address;
} Order;

typedef struct Flour
{
    int id;
    string name;
    double price;
} Flour;

typedef struct Driver
{
    int driverIdNo;
    string driverName;
    string driverLastname;
} Driver;

struct DatabaseFlourCRUD
{
    fstream flourDb;
    //ADD FLOUR
    void addFlour(Flour flour, bool isUpdate, int lastDeletedFlourId)
    {
        system("cls");
        flour.id = 0;
        int lastIncrementedId = 0;
        flourDb.open("floursDb.txt", ios::in | ios::out | ios::app);
        if(isUpdate == 1)
        {
            lastIncrementedId = lastDeletedFlourId;
        }
        else
        {
            do
            {
                flourDb >> flour.id >> flour.name >> flour.price;
                lastIncrementedId = flour.id;
                flourDb >> flour.id >> flour.name >> flour.price;
            }
            while (!flourDb.eof());
        }
        flourDb.close();
        if(lastIncrementedId >= 0)
        {
            flourDb.open("floursDb.txt", ios::in | ios::out | ios::app);
            cout << endl << "Nom de la fleur :";
            cin >> flour.name;
            cout << endl << "Prix de la fleur $(00.00): ";
            cin >> flour.price;
            cout << "Enregistrement reussit..." << endl;
            if(isUpdate)
            {
                flourDb <<lastIncrementedId<<" "<< flour.name<<" "<<flour.price<< endl;

            }
            else
            {
                flourDb <<lastIncrementedId + 1<<" "<< flour.name<<" "<<flour.price<< endl;
            }
            flourDb.close();
        }
        else
        {
            printf("Invalid Id, Merci !\n");
        }
        flourDb.close();
    }

    //DELETE FLOUR
    int deleteFlour(Flour flour)
    {
        system("cls");
        fstream temp;
        temp.open("temp.txt", ios::in | ios::out | ios::app);
        flourDb.open("floursDb.txt", ios::in | ios::out | ios::app);
        int flourTobeDeleted;
        int lastDeletedFlourId = 0;
        cout << endl << "Id de la fleur : ";
        cin >> flourTobeDeleted;
        do
        {
            flourDb >> flour.id >> flour.name >> flour.price;
            if(flourTobeDeleted != flour.id)
            {
                temp <<flour.id <<" "<< flour.name<<" "<<flour.price<< endl;
            }
            else if(flourTobeDeleted == flour.id)
            {
                lastDeletedFlourId = flour.id;
            }
        }
        while (!flourDb.eof());
        temp.close();
        flourDb.close();
        remove("floursDb.txt");
        rename("temp.txt","floursDb.txt");
        return lastDeletedFlourId;
    }

    //VIEW ALL FLOUR
    void viewAllFlours(Flour flour,bool isClientSide)
    {
        if(isClientSide == 0)
        {
            system("cls");
        }
        flourDb.open("floursDb.txt", ios::in | ios::out | ios::app);
        do
        {
            flourDb >> flour.id >> flour.name >> flour.price;
            cout << "----" << endl << "ID: "<< flour.id << endl << "NAME: "<< flour.name << endl << "PRICE: "<< flour.price <<endl;
        }
        while (!flourDb.eof());

        flourDb.close();
    }
    void infoAboutFlour(Flour flour)
    {
        system("cls");
        flourDb.open("floursDb.txt", ios::in | ios::out | ios::app);
        int flourTobeViewed;
        int searchResult = 0;
        cout << endl << "Id de la fleur : ";
        cin >> flourTobeViewed;

        do
        {
            flourDb >> flour.id >> flour.name >> flour.price;
            if(flourTobeViewed == flour.id)
            {
                searchResult+=1;
                cout << "----" << endl << "ID: "<< flour.id << endl << "NAME: "<< flour.name << endl << "PRICE: "<< flour.price;
            }
        }
        while (!flourDb.eof());
        if(searchResult == 0)
        {
            cout << "Aucune fleur trouvee avec ID : " << flourTobeViewed << endl;
        }
        flourDb.close();
    }
};

struct DatabaseDriverCRUD
{
    fstream driverDb;

    void addDriver(Driver driver, bool isUpdate, int lastDeletedDriverId)
    {
        system("cls");
        driver.driverIdNo = 0;
        int lastIncrementedId = 0;
        driverDb.open("driversDb.txt", ios::in | ios::out | ios::app);
        if(isUpdate == 1)
        {
            lastIncrementedId = lastDeletedDriverId;
        }
        else
        {
            do
            {
                driverDb >> driver.driverIdNo >> driver.driverName >> driver.driverLastname;
                lastIncrementedId = driver.driverIdNo;
            }
            while (!driverDb.eof());
        }
        driverDb.close();
        if(lastIncrementedId >= 0)
        {
            driverDb.open("driversDb.txt", ios::in | ios::out | ios::app);
            cout << endl << "Nom du chauffeur : ";
            cin >> driver.driverName;
            cout << endl << "Prenom du chauffeur: ";
            cin >> driver.driverLastname;
            if(isUpdate)
            {
                driverDb <<lastIncrementedId <<" "<< driver.driverName<<" "<<driver.driverLastname<< endl;

            }
            else
            {
                driverDb <<lastIncrementedId + 1 <<" "<< driver.driverName<<" "<<driver.driverLastname<< endl;
            }
            driverDb.close();
        }
        else
        {
            printf("Invalid Id, Merci !\n");
        }
        driverDb.close();
    }

    int deleteDriver(Driver driver)
    {
        system("cls");
        fstream temp;
        temp.open("temp.txt", ios::in | ios::out | ios::app);
        driverDb.open("driversDb.txt", ios::in | ios::out | ios::app);
        int driverTobeDeleted;
        int lastDeletedDriverId = 0;
        cout << endl << "Id du chauffeur : ";
        cin >> driverTobeDeleted;
        do
        {
            driverDb >> driver.driverIdNo >> driver.driverName >> driver.driverLastname;

            if(driverTobeDeleted != driver.driverIdNo)
            {
                temp <<driver.driverIdNo <<" "<< driver.driverName<<" "<<driver.driverLastname<< endl;
            }
            else if(driverTobeDeleted == driver.driverIdNo)
            {
                lastDeletedDriverId = driver.driverIdNo;
            }
        }
        while (!driverDb.eof());
        temp.close();
        driverDb.close();
        remove("driversDb.txt");
        rename("temp.txt","driversDb.txt");
        return lastDeletedDriverId;
    }

    void viewAllDrivers(Driver driver)
    {
        system("cls");
        driverDb.open("driversDb.txt", ios::in | ios::out | ios::app);
        do
        {
            if(driver.driverIdNo == 0){
                break;
            }
            driverDb >> driver.driverIdNo >> driver.driverName >> driver.driverLastname;
            cout << "----" << endl << "ID: "<< driver.driverIdNo << endl << "NAME: "<< driver.driverName << endl << "PRICE: "<< driver.driverLastname <<endl;

        }
        while (!driverDb.eof());

        driverDb.close();
    }

    void infoAboutDriver(Driver driver)
    {
        system("cls");
        driverDb.open("driversDb.txt", ios::in | ios::out | ios::app);
        int driverTobeViewed;
        int searchResult = 0;
        cout << endl << "Id du chauffeur : ";
        cin >> driverTobeViewed;

        do
        {
            driverDb >> driver.driverIdNo >> driver.driverName >> driver.driverLastname;
            if(driverTobeViewed == driver.driverIdNo)
            {
                searchResult+=1;
                cout << "----" << endl << "ID: "<< driver.driverIdNo << endl << "NOM: "<< driver.driverName << endl << "PRENOM: "<< driver.driverLastname;
            }
        }
        while (!driverDb.eof());
        if(searchResult == 0)
        {
            cout << "Aucun chauffeur trouvee avec ID : " << driverTobeViewed << endl;
        }
        driverDb.close();
    }
};

struct Routes
{
    fstream ordersDb;


    void driversManagement()
    {
        DatabaseDriverCRUD databaseDriverCRUD;
        system("cls");
        int menuChoice;
        int lastDeletedDriverId;
        Driver driver;
        printf("\n1. NOUVEAU CHAUFFEUR \n2. SUPPRIMER UN CHAUFFEUR \n3. MODIFIER UN CHAUFFEUR \n4. INFO D'UN CHAUFFEUR \n5. VOIR TOUT LES CHAUFFEURS \n");
        scanf("%i",&menuChoice);
        switch(menuChoice)
        {
        case 1:
            databaseDriverCRUD.addDriver(driver,0,0);
            break;
        case 2:
            lastDeletedDriverId = databaseDriverCRUD.deleteDriver(driver);
            if(lastDeletedDriverId <=0)
            {
                printf("Echec de la suppression, ID invalide\n");
            }
            break;
        case 3:
            lastDeletedDriverId = databaseDriverCRUD.deleteDriver(driver);
            if(lastDeletedDriverId <=0)
            {
                printf("Echec de la modiication, ID invalide\n");
            }
            else
            {
                databaseDriverCRUD.addDriver(driver,1, lastDeletedDriverId);
            }
            break;
        case 4:
            databaseDriverCRUD.infoAboutDriver(driver);
            break;
        case 5:
            databaseDriverCRUD.viewAllDrivers(driver);
            break;
        default:
            printf("Touche invalide, Merci!\n");
            break;
        }
    }

    void viewAllOrders(Order order)
    {
        system("cls");
        ordersDb.open("ordersDb.txt", ios::in | ios::out | ios::app);
        do
        {
            ordersDb >> order.orderIdNo >> order.orderType >> order.clientOrEseName >> order.flourId >> order.address.quartier >> order.address.street >> order.address.number;
            cout << "----" << endl << "ID: "<< order.orderIdNo << endl << "TYPE DE COMMANDE: "<< order.orderType << endl << "CLIENT: "<< order.clientOrEseName << endl << "ID FLEUR: "<< order.flourId << endl << "QUARTIER: "<< order.address.quartier << endl << "AVENUE: "<< order.address.street << endl << "No: " << order.address.number << endl;
        }
        while (!ordersDb.eof());

        ordersDb.close();
    }

    void adminSpace()
    {
        Order order;
        system("cls");
        int adminMainMenuChoice;
        printf("\n1. GERER LES FLEURS \n2. GERER LES CHAUFFEURS\n3. ATTRIBUTION DES COMMANDES AUX CHAUFFEURS\n4. VOIR TOUTES LES COMMANDES DISPONIBLE\n");
        scanf("%i",&adminMainMenuChoice);
        switch(adminMainMenuChoice)
        {
        case 1:
            floursManagement();
            break;
        case 2:
            driversManagement();
            break;
        case 3:
            ordersAssignement();
            break;
        case 4:
            viewAllOrders(order);
            break;
        default:
            printf("Touche invalide, Merci!\n");
            break;
        }
    }

    void floursManagement()
    {
        DatabaseFlourCRUD databaseFlourCRUD{};
        system("cls");
        int menuChoice;
        Flour flour;
        int lastDeletedFlourId;
        cout << endl << "1. NOUVELLE FLEUR \n2. SUPPRIMER UNE FLEUR \n3. MODIFIER UNE FLEUR \n4. INFO D'UNE FLEUR \n5. VOIR TOUTES LES FLEURS \n";
        cin >> menuChoice;
        switch(menuChoice)
        {
        case 1:
            databaseFlourCRUD.addFlour(flour,0,0);
            break;
        case 2:
            lastDeletedFlourId = databaseFlourCRUD.deleteFlour(flour);
            if(lastDeletedFlourId <=0)
            {
                cout << "Echec de la suppression, ID invalide\n" << endl;
            }
            break;
        case 3:
            lastDeletedFlourId = databaseFlourCRUD.deleteFlour(flour);
            if(lastDeletedFlourId <=0)
            {
                cout << "Echec de la modification, ID invalide\n" << endl;
            }
            else
            {
                databaseFlourCRUD.addFlour(flour,1, lastDeletedFlourId);
            }
            break;
        case 4:
            databaseFlourCRUD.infoAboutFlour(flour);
            break;
        case 5:
            databaseFlourCRUD.viewAllFlours(flour,0);
            break;
        default:
            cout << "Touche invalide, Merci!\n" << endl;
            break;
        }
    }
    int ordersAssignement()
    {
        int iddriver;
        int idcommand;
        fstream attribDb;
        fstream driverDb;
        Driver driver;
        Order order;
        cout << "ENTER THE ID OF THE DRIVER : ";
        cin >> iddriver;
        cout << "ENTER THE ID OF THE ORDER  : ";
        cin >> idcommand;
        cout << "ENTER THE START ORDER HOUR : ";
        cin >>order.address.hourTheCommandStart;
        cout << "ENTER THE END ORDER HOUR   : ";
        cin >>order.address.hourTheCommandEnd;

        if(order.address.hourTheCommandEnd <= order.address.hourTheCommandStart)
        {
            cout << "YOUR DEMAND CAN'T BE TREATED... HD >= HF \n... MeRcI";
        }
        else
        {
            ordersDb.open("ordersDb.txt", ios::in | ios::app);
            attribDb.open("attributionDb.txt", ios::in | ios::app);
            driverDb.open("driversDb.txt", ios::in | ios::out|ios::app);
            if(!ordersDb && !attribDb && !driverDb)
            {
                cout << "Databases not found ! \n";
            }
            else
            {
                do
                {
                    driverDb >> driver.driverIdNo >> driver.driverName >> driver.driverLastname;
                    if(driver.driverIdNo == iddriver)
                    {
                        driver.driverIdNo = iddriver;
                        break;
                    }
                }
                while(!driverDb.eof());

                do
                {
                    ordersDb >> order.orderIdNo >> order.orderType >> order.clientOrEseName >> order.flourId >> order.address.quartier >> order.address.street >> order.address.number;
                    if(order.orderIdNo == idcommand)
                    {
                        attribDb << order.orderIdNo <<" "<<order.clientOrEseName<<" "<<driver.driverIdNo<<" "<<order.flourId<<" "<<order.address.quartier<<" "<<order.address.street<<" "<<order.address.number<<" "<<order.address.hourTheCommandStart<<" "<<order.address.hourTheCommandEnd<<"\n";
                        cout<<"operation terminee avec success...100%";
                        break;
                    }
                    else
                    {
                        cout << "writing in file seem impossible check your code"<<endl;
                    }
                }
                while(!ordersDb.eof());
            }
        }
    }
    void clientSpace(Order order, Flour flour)
    {
        DatabaseFlourCRUD databaseFlourCRUD{};
        system("cls");
        int lastIncrementedId = 0;
        ordersDb.open("ordersDb.txt", ios::in | ios::out | ios::app);
        string orderType;
        int orderTypeChoice;
        do
        {
            ordersDb >> order.orderIdNo >> order.orderType >> order.clientOrEseName >> order.flourId >> order.address.quartier >> order.address.street >> order.address.number;
            //cout << "----" << endl << "ID: "<< order.orderIdNo << endl << "TYPE DE COMMANDE: "<< order.orderType << endl << "CLIENT: "<< order.clientOrEseName << endl << "ID FLEUR: "<< order.flourId << endl << "QUARTIER: "<< order.address.quartier << endl << "AVENUE: "<< order.address.street << endl << "No: " << order.address.number << endl;
            lastIncrementedId = order.orderIdNo;
        }
        while (!ordersDb.eof());
        ordersDb.close();
        if(lastIncrementedId >= 0)
        {
            ordersDb.open("ordersDb.txt", ios::in | ios::out | ios::app);
            cout << endl << "Cher client, Bienvenue Chez IZUBA FLEURS !\n Une entreprise de livraison des fleurs a domicile" << endl;
            cout << endl << "LES FLEURS DISPONIBLES EN STOCK" << endl;
            databaseFlourCRUD.viewAllFlours(flour,1);
            cout << endl << endl << "Type de commande:";
            cout << endl << "1. NORMALE" << endl << "2. FUNERAIRES" << endl << "3. ENTREPRISE" << endl;
            cin >> orderTypeChoice;
            switch(orderTypeChoice)
            {
            case 1:
                orderType = "NORMALE";
                break;
            case 2:
                orderType = "FUNERAIRES";
                break;
            case 3:
                orderType = "ENTREPRISE";
                break;
            default:
                printf("Wrong Input\n");
                break;
            }
            cout << endl << endl << "Nom du client/Entreprise :";
            cin >> order.clientOrEseName;
            cout << endl << "Id de la fleur (Reference ci-haut) : ";
            cin >> order.flourId;
            cout << endl << "\nADDRESSE DE LIVRAISON : ";
            cout << endl << "Quartier : ";
            cin >> order.address.quartier;
            cout << endl << "Avenue : ";
            cin >> order.address.street;
            cout << endl << "No : ";
            cin >> order.address.number;
            ordersDb <<lastIncrementedId + 1 <<" "<< orderType<<" "<<order.clientOrEseName<<" "<<order.flourId<<" "<<order.address.quartier<<" "<<order.address.street<<" "<<order.address.number;
            ordersDb.close();
        }
        else
        {
            printf("Invalid Id, Merci !\n");
        }
    }

    void driverspace(){
        int result = 0;
        int driverNo;
        fstream attribDb;
        fstream driverDb;
        Driver driver;
        Order order;
        system("cls");
        cout << "\tTACHES EN COURS" << endl;
        cout << "\t===============" << endl <<endl;
        cout << "ENTER THE ID OF THE DRIVER : ";
        cin >> driverNo;
        cout << "=========================  ==" << endl <<endl;
        attribDb.open("attributionDb.txt", ios::in | ios::app);
        if(!attribDb)
        {
            cout << "Database not found ! \n";
        }
        else
        {
            do
            {
                attribDb>>order.orderIdNo>>order.clientOrEseName>>driver.driverIdNo>>order.flourId>>order.address.quartier>>order.address.street>>order.address.number>>order.address.hourTheCommandStart>>order.address.hourTheCommandEnd;
                if(driver.driverIdNo == driverNo)
                {
                    result += 1;
                    //cout << "FLOUR DETAILS WITH THE ID No : " << flourId << endl;
                    cout << "ORDER No : " << order.orderIdNo << " \n";
                    cout << "ORDER CLIENT NAME : " << order.clientOrEseName<< endl;
                    cout << "ORDER FLOUR ID    : " << order.flourId<< endl;
                    cout << "ORDER ADDRESS QUARTIER : " << order.address.quartier << endl;
                    cout << "ORDER ADDRESS STREET   : " << order.address.street << endl;
                    cout << "ORDER ADDRESS HOUSE No : " << order.address.number << endl;
                    cout << "ORDER HOUR TO START    : " << order.address.hourTheCommandStart << endl;
                    cout << "ORDER HOUR TO END      : " << order.address.hourTheCommandEnd << endl;


                }
            }
            while(!attribDb.eof());
            if(result==0){
                    cout << "You don't have any command to deliver... thank you \n";
            }
        }
        attribDb.close();
    }


};

int main()
{
    Routes routes;
    int mainMenuChoice;
    int clientMainMenuChoice;
    Order order;
    Flour flour;
    printf("\nBienvenue Chez IZUBA FLEURS !\nUne entreprise de livraison des fleurs � domicile.\n");
    printf("\n1. ADMINISTRATEUR \n2. CLIENT\n3. CHAUFFEUR\n");
    scanf("%i",&mainMenuChoice);
    switch(mainMenuChoice)
    {
    case 1:
        routes.adminSpace();
        break;
    case 2:
        routes.clientSpace(order,flour);
        break;
    case 3:
        routes.driverspace();
        break;
    default:
        printf("Touche invalide, Merci!\n");
        break;
    }
    return 0;
}
