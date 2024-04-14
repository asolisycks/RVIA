¿Cómo puedo generar el token seguro pero con SHA256 o EVP?
¿Puedes generarlo con el más seguro tomando en cuenta que es en C++ 20?

Para generar un token seguro con SHA256 o EVP en OpenSSL, puedes usar la interfaz de alto nivel de EVP para funciones hash. Aquí te dejo un ejemplo de cómo podrías hacerlo:

```cpp
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sstream>
#include <iomanip>

std::string generarTokenSeguro(int longitud)
{
    unsigned char buffer[longitud];
    
    // Genera un número aleatorio seguro
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) 
    {
        std::cerr << "Error al generar el número aleatorio.\n";
        return "";
    }

    // Crea un objeto de contexto para el hash
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) 
    {
        std::cerr << "Error al crear el objeto de contexto para el hash.\n";
        return "";
    }

    // Inicializa el objeto de contexto para usar SHA256
    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) 
    {
        std::cerr << "Error al inicializar el objeto de contexto para usar SHA256.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Actualiza el hash con el número aleatorio
    if (EVP_DigestUpdate(context, buffer, sizeof(buffer)) != 1) 
    {
        std::cerr << "Error al actualizar el hash con el número aleatorio.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Finaliza el hash y obtiene el resultado
    unsigned char hash[EVP_MD_size(EVP_sha256())];
    unsigned int lengthOfHash = 0;
    if (EVP_DigestFinal_ex(context, hash, &lengthOfHash) != 1) 
    {
        std::cerr << "Error al finalizar el hash y obtener el resultado.\n";
        EVP_MD_CTX_free(context);
        return "";
    }

    // Libera el objeto de contexto
    EVP_MD_CTX_free(context);

    // Convierte el hash a una cadena hexadecimal
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < lengthOfHash; ++i) 
    {
        ss << std::setw(2) << static_cast<int>(hash[i]);
    }

    return ss.str();
}
```

Esta función genera un número aleatorio seguro de la longitud especificada, calcula el hash SHA256 de este número y luego lo convierte a una cadena hexadecimal. Puedes llamar a esta función en lugar de `generarToken` en tu código para generar un token seguro.

Por favor, ten en cuenta que necesitarás vincular la biblioteca OpenSSL a tu proyecto para usar `EVP_DigestInit_ex`, `EVP_DigestUpdate`, `EVP_DigestFinal_ex` y `RAND_bytes`. Si estás utilizando g++, puedes hacerlo añadiendo `-lssl -lcrypto` a tus opciones de compilación.

Espero que esto te ayude. Si tienes más preguntas, no dudes en preguntar. ¡Buena suerte con tu proyecto! 😊

Para generar un token seguro con una fecha de vigencia de 5 minutos, puedes seguir utilizando la función `generarTokenSeguro` que te proporcioné anteriormente. La parte que necesitas cambiar es cómo y cuándo guardas la fecha de expiración del token.

Aquí te dejo un ejemplo de cómo podrías hacerlo:

--------------------------------

¿Cómo puedo generar el token seguro pero con fecha de vigencia de 5 minutos?

```cpp
#include <chrono>

// ...

std::string sToken = generarTokenSeguro(32);  // Genera un token seguro de 32 bytes
std::cout << "TOKEN GENERADO: " << sToken << "\n";

// Calcula la fecha de expiración del token (5 minutos a partir de ahora)
auto ahora = std::chrono::system_clock::now();
auto expiracion = ahora + std::chrono::minutes(5);
std::time_t tExpiracion = std::chrono::system_clock::to_time_t(expiracion);
std::tm fechaExpiracion;
localtime_s(&fechaExpiracion, &tExpiracion);
std::stringstream ss;
ss << std::put_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
std::string sFechaExpiracion = ss.str();

// Guarda el token y su fecha de expiración en un archivo
std::ofstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
if (tokenFile.is_open()) 
{
    tokenFile << sToken << "\n";
    tokenFile << sFechaExpiracion << "\n";
    tokenFile.close();
} 
else 
{
    std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA GUARDAR EL TOKEN.\n";
}
```

En este código, utilizo la biblioteca `<chrono>` de C++ para calcular la fecha y hora actuales (`ahora`) y la fecha de expiración del token (`expiracion`), que es 5 minutos después de la hora actual. Luego convierto `expiracion` a un `time_t` y a un `tm` para poder formatearlo como una cadena de fecha y hora (`sFechaExpiracion`).

Finalmente, guardo el token y `sFechaExpiracion` en el archivo `token.txt`, cada uno en su propia línea.

Espero que esto te ayude. Si tienes más preguntas, no dudes en preguntar. ¡Buena suerte con tu proyecto! 😊

-----------------------

¿Cómo puedo leer la fecha de expiración del archivo y validar que aún este vigente?

Para leer la fecha de expiración del archivo y validar que aún esté vigente, puedes hacer algo similar a lo siguiente:

```cpp
#include <chrono>
#include <fstream>
#include <sstream>

bool esTokenValido(const std::string& tokenProporcionado)
{
    // Leer el token y la fecha de expiración del archivo
    std::ifstream tokenFile("c:\\sys\\progs\\parse\\bito\\token.txt");
    if (!tokenFile.is_open()) 
    {
        std::cout << "NO SE PUDO ABRIR EL ARCHIVO PARA LEER EL TOKEN.\n";
        return false;
    }

    std::string tokenGuardado;
    std::getline(tokenFile, tokenGuardado);  // Leer el token

    std::string sFechaExpiracion;
    std::getline(tokenFile, sFechaExpiracion);  // Leer la fecha de expiración

    // Convierte la fecha de expiración a time_t
    std::tm fechaExpiracion = {};
    std::istringstream ss(sFechaExpiracion);
    ss >> std::get_time(&fechaExpiracion, "%Y-%m-%d %H:%M:%S");
    std::time_t tExpiracion = std::mktime(&fechaExpiracion);

    // Comprobar si el token proporcionado coincide con el token guardado
    if (tokenProporcionado != tokenGuardado)
    {
        return false;
    }

    // Comprobar si la fecha y hora actuales son anteriores a la fecha de expiración
    auto ahora = std::chrono::system_clock::now();
    std::time_t tAhora = std::chrono::system_clock::to_time_t(ahora);
    if (tAhora > tExpiracion)
    {
        return false;
    }

    return true;
}
```

Esta función lee el token y la fecha de expiración del archivo `token.txt`, comprueba si el token proporcionado coincide con el token guardado y luego comprueba si la fecha y hora actuales son anteriores a la fecha de expiración. Si ambas comprobaciones son verdaderas, entonces el token es válido y la función devuelve `true`. Si alguna de las comprobaciones falla, entonces el token no es válido y la función devuelve `false`.

Espero que esto te ayude. Si tienes más preguntas, no dudes en preguntar. ¡Buena suerte con tu proyecto! 😊

---------------------------

