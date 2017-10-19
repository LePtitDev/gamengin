#ifdef GL_ES

// Définie la précision par défaut à moyen
precision mediump int;
precision mediump float;

#endif

// Matrice de projection
uniform mat4 m_projection;

// Coordonnées du sommet
attribute vec4 a_position;

// Coordonnées sur la texture (en entrée)
attribute vec2 a_texcoord;

// Coordonnées sur la texture (en sortie)
varying vec2 v_texcoord;

// Fonction d'entrée
void main() {
	// Calcule la position du sommet projeté
    gl_Position = m_projection * a_position;

	// Transmet les coordonnées de texture au fragment shader
	// La valeur est automatiquement interpolée aux fragments sur la face du polygone
    v_texcoord = a_texcoord;
}
