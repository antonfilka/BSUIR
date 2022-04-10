package antonfilippovich.javakpp.restservice.entity;

import lombok.AllArgsConstructor;
import lombok.Data;

@AllArgsConstructor
@Data
public class ShifterEntity {

    private String textToShift;
    private String shiftedText;
}
