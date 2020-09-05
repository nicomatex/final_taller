/*
3) Declare la clase TELEFONO para encapsular una cadena numérica correspondiente a un
teléfono. Incluya al menos: Constructor(area, numero), Constructor move y Constructor de
Copia; Operador <<, ==, =, long y >>. Implemente el operador >>.
*/
#include <string>

class Telefono{
    private:
        std::string numero;
    public:
        Telefono(std::string area, std::string numero);
        Telefono(const Telefono& other);
        Telefono(Telefono&& other);

        friend std::ostream& operator<<(std::ostream& stream, const Telefono& telefono);
        friend std::istream& operator>>(std::istream& stream, Telefono& telefono);

        Telefono& operator=(const Telefono& other);
        Telefono& operator=(Telefono&& other);

        bool operator==(const Telefono& other) const;
        operator long() const;
};
