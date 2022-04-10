package antonfilippovich.javakpp.restservice.logger;

import org.apache.logging.log4j.Level;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class EventsLogger {
    private static final Logger logger = LogManager.getLogger(EventsLogger.class);

    public static void Log(Level level, Object message) {
        logger.log(level, message);
    }
}
