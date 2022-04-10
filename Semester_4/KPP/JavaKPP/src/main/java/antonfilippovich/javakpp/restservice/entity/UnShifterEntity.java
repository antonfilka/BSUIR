package antonfilippovich.javakpp.restservice.entity;

import lombok.AllArgsConstructor;
import lombok.Data;

@AllArgsConstructor
@Data
public class UnShifterEntity {

    private String textToUnShift;
    private String unShiftedText;
}
