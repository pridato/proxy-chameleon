import requests

def send_get_request_via_proxy(proxy_url, target_url, params=None):
    """Envía una solicitud GET a través del proxy.

    Args:
        proxy_url (str): La URL de tu proxy (por ejemplo, http://localhost:8080).
        target_url (str): La URL del servidor final al que se debe reenviar la solicitud.
        params (dict): Parámetros opcionales para la solicitud GET.

    Returns:
        Response: La respuesta del servidor.
    """
    try:
        proxies = {
            'http': proxy_url,
            'https': proxy_url,
        }

        # Enviar la solicitud GET a través del proxy
        response = requests.get(target_url, params=params, proxies=proxies)
        response.raise_for_status()  # Lanza una excepción para respuestas con error HTTP
        return response
    except requests.RequestException as e:
        print(f"Error en la solicitud GET: {e}")
        return None

if __name__ == "__main__":
    proxy_url = "http://localhost:8080"

    target_url_get = "http://httpbin.org/get"  

    response = send_get_request_via_proxy(proxy_url, target_url_get)
    if response:
        print("Respuesta GET:")
        print(response.text)
