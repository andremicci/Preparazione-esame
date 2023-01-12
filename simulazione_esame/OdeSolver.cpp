#include "Vector.h"
#include "OdeSolver.h"

void OdeSolver::SetMatPoint(MatPoint tmp)
{
  m_p.push_back(tmp);
}

void OdeSolver::SetMethod(string method)
{
  m_method = method;
}

vector<MatPoint> OdeSolver::GetMatPoints()
{
  return m_p;
}

MatPoint OdeSolver::GetMatPoint(unsigned int i)
{
  return m_p[i];
}

string OdeSolver ::GetMethod()
{
  return m_method;
}

unsigned int OdeSolver::N()
{
  return m_p.size();
}

void OdeSolver::T(double t0)
{
  m_t = t0;
}

double OdeSolver::T()
{
  return m_t;
}

void OdeSolver::Step(double h)
{
  m_h = h;
}

double OdeSolver::Step()
{
  return m_h;
}

Vector OdeSolver::m_eqDiff(unsigned int i, double t, vector<MatPoint> p)
{
  //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
  Vector F;
  Vector a;
  for (long unsigned int j = 0; j < p.size(); j++)
  {
    F = F + fInternal(i, j, t, p);
  }
  F = F + fExternal(i, t, p);
  a = F * (1 / p[i].Mass());
  return a;
}


//Da implementare a cura dello studente
void OdeSolver::Solve()
{

  if (m_method == "Eulero")
  {

    vector<Vector> k1(m_p.size());
    vector<Vector> w1(m_p.size());
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      k1[i] = m_h * m_p[i].V();
      w1[i] = m_h * m_eqDiff(i, m_t, m_p);
    }

    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }
    m_t += m_h;
  }

  else if (m_method == "Rk2")
  {  
    //cout << "entro in rk2"<< endl;
    // STEP 5 implementare Runge Kutta al secondo ordine
    vector<Vector> k1(m_p.size());
    vector<Vector> w1(m_p.size());
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      k1[i] = m_h * m_p[i].V();
      w1[i] = m_h * m_eqDiff(i, m_t, m_p);
    }

    vector<Vector> k2(m_p.size());
    vector<Vector> w2(m_p.size());
    vector<MatPoint> p2(m_p);

    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      p2[i].V(m_p[i].V() + w1[i] * (0.5));
      p2[i].R(m_p[i].R() + k1[i] * (0.5));
    }
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      k2[i] = m_h * (m_p[i].V() + w1[i] * (0.5));

      w2[i] = m_h * m_eqDiff(i, m_t, p2);
    }
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }
    m_t += m_h;
  }
  else if (m_method == "Verlet")
  {

    vector<Vector> an(m_p.size());

    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      an[i] = m_eqDiff(i, m_t, m_p);
    }

    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      m_p[i].R(m_p[i].R() + m_h * m_p[i].V() + (0.5) * pow(m_h, 2) * an[i]); //m_eqDiff(i, m_t, m_p) non va bene
    }
   
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      m_p[i].V(m_p[i].V() + (m_h * 0.5) * (m_eqDiff(i, m_t, m_p) + an[i]));
    }

    m_t += m_h;
  }

  else if(m_method=="Rk4"){

    vector<Vector> k1(m_p.size());
    vector<Vector> w1(m_p.size());
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      k1[i] = m_h * m_p[i].V();
      w1[i] = m_h * m_eqDiff(i, m_t, m_p);
    }

    vector<Vector> k2(m_p.size());
    vector<Vector> w2(m_p.size());
    vector<MatPoint> p2(m_p);

    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      p2[i].V(m_p[i].V() + w1[i] * (0.5));
      p2[i].R(m_p[i].R() + k1[i] * (0.5));
    }
    
    for (unsigned int i = 0; i < m_p.size(); i++)
    {
      k2[i] = m_h * (m_p[i].V() + w1[i] * (0.5));

      w2[i] = m_h * m_eqDiff(i, m_t, p2);
    }
   

    vector<Vector> k3(m_p.size());
    vector<Vector> w3(m_p.size());
    vector<MatPoint> p3(m_p);

    for(unsigned int i=0;i <m_p.size();i++){
      p3[i].V(m_p[i].V()+w2[i]*(0.5));
      p3[i].R(m_p[i].R()+k2[i]*(0.5));
    }
    for(unsigned int i=0;i<m_p.size();i++){
      k3[i]=m_h*(m_p[i].V()+w2[i]*(0.5));
      w3[i]=m_h*m_eqDiff(i,m_t,p3);
    }
    
    
    vector<Vector> k4(m_p.size());
    vector<Vector> w4(m_p.size());
    vector<MatPoint> p4(m_p);
    
     for(unsigned int i=0;i <m_p.size();i++){
      p4[i].V(m_p[i].V()+w3[i]);
      p4[i].R(m_p[i].R()+k3[i]);
    }
  
    for(unsigned int i=0;i<m_p.size();i++){
      k4[i]=m_h*(m_p[i].V()+w3[i]);
      w4[i]=m_h*m_eqDiff(i,m_t,p4);
    }

       for (unsigned int i = 0; i < m_p.size(); i++)
    {
      m_p[i].R(m_p[i].R() + k1[i]*(1.0/6.0)+k2[i]*(1.0/3.0)+k3[i]*(1.0/3.0)+k4[i]*(1.0/6.0));
      
      m_p[i].V(m_p[i].V() + w1[i]*(1.0/6.0)+w2[i]*(1.0/3.0)+w3[i]*(1.0/3.0)+w4[i]*(1.0/6.0));
      
    }
 

    m_t += m_h;
  }




  
}
