package entidades;

public abstract class Pessoa {

    private String nome;
    protected double idade;
    
    
    public Pessoa(){
    }
    
    public void setIdade(double idade){
        
        this.idade = idade;
    }
    
    public void setNome(String string){
        
        this.nome = string;
    }
    
    public String getNome(){
        
        return this.nome;
    }
    
    public double getIdade(){
        
        return this.idade;
    }
    
}
