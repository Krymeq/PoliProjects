package confirmationLetter;

import com.oracle.webservices.internal.api.message.PropertySet;

public class RequestContext {
    private PropertySet conversationScope;

    public PropertySet getConversationScope() {
        return conversationScope;
    }

    public void setConversationScope(PropertySet conversationScope) {
        this.conversationScope = conversationScope;
    }
}
