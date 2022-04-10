package antonfilippovich.javakpp.restservice.exceptions;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(value = HttpStatus.INTERNAL_SERVER_ERROR, reason = "Wrong value...")
public class InternalException extends RuntimeException {
    public InternalException(String message) {
        super(message);
    }
}
