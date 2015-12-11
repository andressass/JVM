package entidades;

public class Aluno extends Pessoa {

    private String nome;
    private int matricula = 12345;
    public long serie;
    protected double idade;
    
    
    public Aluno(int serie){
        this.serie = serie;
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
    

    public int getMatricula(){
        
        return this.matricula;
    }
    
    public int setMatricula(){
        
        return this.matricula;
    }
    
    public void setSerie(long serie){
        
        this.serie = serie;
    }
    
    public long getSerie(){
        
        return this.serie;
    }
    
    public double getIdadeVerdadeira(){
        
        return this.idade + 20;
    }

}
