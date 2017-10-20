#ifdef GL_ES

// D�finie la pr�cision par d�faut � moyen
precision mediump int;
precision mediump float;

#endif

// Texture
uniform sampler2D texture;

// Coordonn�es sur la texture (en entr�e)
varying vec2 v_texcoord;

// Fonction d'entr�e
void main() {
	// Assigne la couleur du fragment par rapport � la texture
    gl_FragColor = texture2D(texture, v_texcoord);
}
