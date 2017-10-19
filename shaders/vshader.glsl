#ifdef GL_ES

// D�finie la pr�cision par d�faut � moyen
precision mediump int;
precision mediump float;

#endif

// Matrice de projection
uniform mat4 m_projection;

// Coordonn�es du sommet
attribute vec4 a_position;

// Coordonn�es sur la texture (en entr�e)
attribute vec2 a_texcoord;

// Coordonn�es sur la texture (en sortie)
varying vec2 v_texcoord;

// Fonction d'entr�e
void main() {
	// Calcule la position du sommet projet�
    gl_Position = m_projection * a_position;

	// Transmet les coordonn�es de texture au fragment shader
	// La valeur est automatiquement interpol�e aux fragments sur la face du polygone
    v_texcoord = a_texcoord;
}
