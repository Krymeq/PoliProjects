package domain;

import record.parser.FileExtension;

import java.math.BigDecimal;
import java.util.List;

public class ConfirmationLetter {
    private FileExtension extension;
    private Currency currency;
    private String hashTotalCredit;
    private String hashTotalDebit;
    private String batchTotalCredit;
    private String batchTotalDebit;
    private String totalProcessedRecords;
    private String transactionCost;
    private String transferType;
    private List<AmountAndRecordsPerBank> banks;
    private List<FaultRecord> creditingErrors;
    private Client client;
    private String branchName;
    private BigDecimal retrievedAmountEur;
    private BigDecimal retrievedAmountUsd;
    private BigDecimal retrievedAmountFL;
    private Integer totalRetrievedRecords;

    public FileExtension getExtension() {
        return extension;
    }

    public void setExtension(FileExtension extension) {
        this.extension = extension;
    }

    public Currency getCurrency() {
        return currency;
    }

    public void setCurrency(Currency currency) {
        this.currency = currency;
    }

    public String getHashTotalCredit() {
        return hashTotalCredit;
    }

    public void setHashTotalCredit(String hashTotalCredit) {
        this.hashTotalCredit = hashTotalCredit;
    }

    public String getHashTotalDebit() {
        return hashTotalDebit;
    }

    public void setHashTotalDebit(String hashTotalDebit) {
        this.hashTotalDebit = hashTotalDebit;
    }

    public String getBatchTotalCredit() {
        return batchTotalCredit;
    }

    public void setBatchTotalCredit(String batchTotalCredit) {
        this.batchTotalCredit = batchTotalCredit;
    }

    public String getBatchTotalDebit() {
        return batchTotalDebit;
    }

    public void setBatchTotalDebit(String batchTotalDebit) {
        this.batchTotalDebit = batchTotalDebit;
    }

    public String getTotalProcessedRecords() {
        return totalProcessedRecords;
    }

    public void setTotalProcessedRecords(String totalProcessedRecords) {
        this.totalProcessedRecords = totalProcessedRecords;
    }

    public String getTransactionCost() {
        return transactionCost;
    }

    public void setTransactionCost(String transactionCost) {
        this.transactionCost = transactionCost;
    }

    public String getTransferType() {
        return transferType;
    }

    public void setTransferType(String transferType) {
        this.transferType = transferType;
    }

    public List<AmountAndRecordsPerBank> getBanks() {
        return banks;
    }

    public void setBanks(List<AmountAndRecordsPerBank> banks) {
        this.banks = banks;
    }

    public List<FaultRecord> getCreditingErrors() {
        return creditingErrors;
    }

    public void setCreditingErrors(List<FaultRecord> creditingErrors) {
        this.creditingErrors = creditingErrors;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public String getBranchName() {
        return branchName;
    }

    public void setBranchName(String branchName) {
        this.branchName = branchName;
    }

    public BigDecimal getRetrievedAmountEur() {
        return retrievedAmountEur;
    }

    public void setRetrievedAmountEur(BigDecimal retrievedAmountEur) {
        this.retrievedAmountEur = retrievedAmountEur;
    }

    public BigDecimal getRetrievedAmountUsd() {
        return retrievedAmountUsd;
    }

    public void setRetrievedAmountUsd(BigDecimal retrievedAmountUsd) {
        this.retrievedAmountUsd = retrievedAmountUsd;
    }

    public BigDecimal getRetrievedAmountFL() {
        return retrievedAmountFL;
    }

    public void setRetrievedAmountFL(BigDecimal retrievedAmountFL) {
        this.retrievedAmountFL = retrievedAmountFL;
    }

    public Integer getTotalRetrievedRecords() {
        return totalRetrievedRecords;
    }

    public void setTotalRetrievedRecords(Integer totalRetrievedRecords) {
        this.totalRetrievedRecords = totalRetrievedRecords;
    }
}
