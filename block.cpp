
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Date;

class TransactionData {
public double amount;
public String receiverKey;
public String senderKey;
public long timeStamp;

public TransactionData(double amount, String receiverKey, String senderKey, long timeStamp) {
    this.amount = amount;
    this.receiverKey = receiverKey;
    this.senderKey = senderKey;
    this.timeStamp = timeStamp;
}
     public String getSenderKey() {
        return this.senderKey;
    }

    public void setSenderKey(String senderKey) {
        this.senderKey = senderKey;
    }

    public String getReceiverKey() {
        return receiverKey;
    }

    public void setReceiverKey(String receiverKey) {
        this.receiverKey = receiverKey;
    }

    public int getAmount() {
        return (int)amount;
    }

    public void setAmount(int amount) {
        this.amount = amount;
    }
}


class Block {
private int index;
private ArrayList<TransactionData> data;
private BigInteger previousHash;
private BigInteger hash;
private long timeStamp;
private int nonce;

public Block(int index, ArrayList<TransactionData> data, BigInteger previousHash) {
    this.index = index;
    this.data = data;
    this.previousHash = previousHash;
    this.timeStamp = new Date().getTime();
    this.nonce = 0;
    this.hash = calculateHash();
}

public BigInteger calculateHash() {
    String dataHash = "";
    for (TransactionData transaction : data) {
        String amountStr = Double.toString(transaction.amount);
        dataHash += amountStr + transaction.receiverKey + transaction.senderKey + transaction.timeStamp;
    }
    String blockHash = this.previousHash.toString() + Long.toString(this.timeStamp) + Integer.toString(this.nonce) + dataHash;
    return new BigInteger(blockHash);
}


public void mineBlock(int difficulty) {
    String target = new String(new char[difficulty]).replace('\0', '0');
    while (!this.hash.toString(16).substring(0, difficulty).equals(target)) {
        this.nonce++;
        this.hash = calculateHash();
    }
    System.out.println("Block mined with hash: " + this.hash);
}

public int getIndex() {
    return index;
}

public ArrayList<TransactionData> getData() {
    return data;
}

public BigInteger getPreviousHash() {
    return previousHash;
}

public BigInteger getHash() {
    return hash;
}
}

class Blockchain {
private ArrayList<Block> chain;
private int difficulty;

public Blockchain(int difficulty) {
    this.chain = new ArrayList<Block>();
    this.difficulty = difficulty;
    this.chain.add(createGenesisBlock());
}

private Block createGenesisBlock() {
    String genesisData = "This is the beginning of the blockchain!";
    return new Block(0, new ArrayList<TransactionData>(), new BigInteger("0"));
}

public Block getLatestBlock() {
    return this.chain.get(this.chain.size() - 1);
}

public void addBlock(TransactionData data) {
    Block newBlock = new Block(this.chain.size(), new ArrayList<TransactionData>() {{ add(data); }}, getLatestBlock().getHash());
    newBlock.mineBlock(difficulty);
    this.chain.add(newBlock);
}

public boolean isChainValid() {
    for (int i = 1; i < this.chain.size(); i++) {
        Block currentBlock = this.chain.get(i);
        Block previousBlock = this.chain.get(i - 1);

        if (!currentBlock.getHash().equals(currentBlock.calculateHash())) {
            return false;
        }

        if (!currentBlock.getPreviousHash().equals(previousBlock.getHash())) {
            return false;
        }
    }
    return true;
}
}
public class Main {
    public static void main(String[] args) {

        Blockchain TWSCCoin = new Blockchain(4);

        TransactionData data1 = new TransactionData(1.5, "Utkarsh Tripathi", "Akshat Mehra", new Date().getTime());

        TWSCCoin.addBlock(data1);

        System.out.println("Is chain Valid?");
        System.out.println(TWSCCoin.isChainValid());

        TransactionData data2 = new TransactionData(1.5, "Akshat Jaimini", "Amit Goyal", new Date().getTime());

        TWSCCoin.addBlock(data2);

        System.out.println("Now is the chain valid?");
        System.out.println(TWSCCoin.isChainValid());

        Block hackBlock = TWSCCoin.getLatestBlock();
        hackBlock.getData().get(0).setAmount(10000);
        hackBlock.getData().get(0).setReceiverKey("Akshavya - From Crypto Enthusiasts");


        System.out.println("Now is the chain still valid?");
        System.out.println(TWSCCoin.isChainValid());
    }
}
