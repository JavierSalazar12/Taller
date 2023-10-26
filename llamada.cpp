#include <iostream>
#include <stack>
#include <unordered_map>

struct Contact {
    std::string name;
    std::string number;
};

class CallStack {
private:
    std::stack<Contact> mainStack;
    std::unordered_map<std::string, Contact> contactMap;

public:
    void push() {
        std::string number;
        std::cout << "Ingrese el número de teléfono: ";
        std::cin >> number;

        auto it = contactMap.find(number);
        if (it != contactMap.end()) {
            // El número ya existe en la pila
            // Lo extraemos y lo colocamos en el top de la pila principal
            Contact contact = it->second;
            extractNumber(number);
            mainStack.push(contact);
        } else {
            // El número no existe en la pila
            std::string name;
            std::cout << "Ingrese el nombre del contacto: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            Contact contact;
            contact.name = name;
            contact.number = number;
            mainStack.push(contact);
            contactMap[number] = contact;
        }
    }

    void viewer() {
        std::stack<Contact> tmpStack = mainStack;

        std::cout << "Historial de llamadas:\n";
        while (!tmpStack.empty()) {
            Contact contact = tmpStack.top();
            std::cout << "Nombre: " << contact.name << ", Número: " << contact.number << std::endl;
            tmpStack.pop();
        }
    }

    void pop() {
        if (!mainStack.empty()) {
            Contact contact = mainStack.top();
            mainStack.pop();
            contactMap.erase(contact.number);
        } else {
            std::cout << "La pila está vacía. No se pueden eliminar más elementos.\n";
        }
    }

private:
    void extractNumber(const std::string& number) {
        std::stack<Contact> tmpStack;

        while (!mainStack.empty()) {
            Contact contact = mainStack.top();
            mainStack.pop();

            if (contact.number == number) {
                break; // Encontramos el número a extraer
            }

            tmpStack.push(contact);
        }

        // Devolvemos los números de la pila auxiliar a la pila principal
        while (!tmpStack.empty()) {
            Contact contact = tmpStack.top();
            tmpStack.pop();
            mainStack.push(contact);
        }
    }
};

int main() {
    CallStack callStack;

    int option;
    do {
        std::cout << "1. Agregar llamada\n";
        std::cout << "2. Mostrar historial de llamadas\n";
        std::cout << "3. Eliminar última llamada\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opción: ";
        std::cin >> option;

        switch (option) {
            case 1:
                callStack.push();
                break;
            case 2:
                callStack.viewer();
                break;
            case 3:
                callStack.pop();
                break;
            case 4:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
        }

        std::cout << std::endl;
    } while (option != 4);

    return 0;
}