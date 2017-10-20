#ifdef GL_ES

// Définie la précision par défaut à moyen
precision mediump int;
precision mediump float;

#endif

// Texture
uniform sampler2D texture;

// Coordonnées sur la texture (en entrée)
varying vec2 v_texcoord;

// Fonction d'entrée
void main() {
	// Assigne la couleur du fragment par rapport à la texture
    gl_FragColor = texture2D(texture, v_texcoord);
}
