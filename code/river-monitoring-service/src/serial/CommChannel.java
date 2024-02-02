package serial;

/**
 * Simple interface for an async msg communication channel
 *
 * @author aricci
 */
public interface CommChannel {

    /**
     * Send a message represented by a string (without new line).
     * <p>
     * Asynchronous model.
     *
     * @param msg
     */
    void sendMsg(String msg);

    /**
     * To receive a message.
     * <p>
     * Uses a timeout of 10 milliseconds and return null if no message was found.
     */
    String receiveMsg() throws InterruptedException;

    /**
     * To check if a message is available.
     *
     * @return
     */
    boolean isMsgAvailable();

}
