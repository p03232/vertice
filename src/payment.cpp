# include "payment.h"

# include <cstdlib>
# include <string>
# include <string.h>

/* Simula o gateway de pagamentos, que aceita o pagamento quando a chave foi informada e o valor é positivo. */
static bool gatewayAuthorize(const char *key, double amount)
{
    return key[0] != '\0' && amount > 0.0;
}

/* Autoriza o pagamento com a chave do gateway e apaga a chave da memória logo depois do uso. */
bool processPayment(double amount)
{
    const char *configuredKey = std::getenv("PAYMENT_KEY");
    if (configuredKey == nullptr || configuredKey[0] == '\0')
    {
        return false;
    }

    std::string key(configuredKey);
    bool authorized = gatewayAuthorize(key.c_str(), amount);
    memset(key.data(), 0, key.size());
    return authorized;
}
