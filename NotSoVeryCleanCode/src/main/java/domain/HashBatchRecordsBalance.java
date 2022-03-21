package domain;

import java.math.BigDecimal;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class HashBatchRecordsBalance {

    private BigDecimal hashTotalCredit;
    private BigDecimal hashTotalDebit;
    private Map<Integer, BatchTotal> batchTotals;
    private BigDecimal totalFee;
    private String collectionType;

    public HashBatchRecordsBalance() {
        hashTotalCredit = BigDecimal.ZERO;
        hashTotalDebit = BigDecimal.ZERO;
        batchTotals = new HashMap<>();
        totalFee = BigDecimal.ZERO;
        collectionType = "";
    }

    public BigDecimal getHashTotalCredit() {
        return hashTotalCredit;
    }

    public void setHashTotalCredit(BigDecimal hashTotalCredit) {
        this.hashTotalCredit = hashTotalCredit;
    }

    public BigDecimal getHashTotalDebit() {
        return hashTotalDebit;
    }

    public void setHashTotalDebit(BigDecimal hashTotalDebit) {
        this.hashTotalDebit = hashTotalDebit;
    }

    public void setBatchTotals(Map<Integer, BatchTotal> batchTotals) {
        this.batchTotals = batchTotals;
    }

    public void setTotalFee(BigDecimal totalFee) {
        this.totalFee = totalFee;
    }

    public void setCollectionType(String collectionType) {
        this.collectionType = collectionType;
    }

    public Map<Integer, BatchTotal> getBatchTotals() {
        return batchTotals;
    }

    public Integer getRecordsTotal()
    {
        return batchTotals.size();
    }

    public BigDecimal getTotalFee() {
        return totalFee;
    }

    public String getCollectionType() {
        return collectionType;
    }

    public BigDecimal getBatchTotal(Integer amountDivider, String sign) {
        BigDecimal sum = BigDecimal.ZERO;
        for (BatchTotal total : batchTotals.values()) {
            sum = sum.add(total.getTotalForSign(sign));
        }
        return sum.divide(new BigDecimal(amountDivider));
    }
}
