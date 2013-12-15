uniform sampler2DRect src_tex_unit0;
uniform vec2 sampleDivisor;
uniform vec2 depthPoint;

vec2 samplePos;

void main( void )
{
    
    vec2 st		= gl_TexCoord[0].st;

//    float maxX = depthPoint.x + 20.0;
//    float minX = depthPoint.x - 20.0;
//    
//    float maxY = depthPoint.y +  20.0;
//    float minY = depthPoint.y - 20.0;
    
//    
//    for(float i=0.;i<10.;i++){
//        vec2 max = depthPoint + vec2(20.*i);
//        vec2 min = depthPoint - vec2(20.*i);
//    	if( st.s >= min.x && st.s <= max.x && st.t >= min.y && st.t <= max.y){
//          //  vec2 divisor = sampleDivisor * 1.5;
//            //    float divisor1 = sampleDivisor.y * 1.5;
//            
//            samplePos = st.st - mod( st.st, vec2(10./i) );
//        }else{
//            samplePos = st.st;
//
//        }
//    }
    
    vec2 max = depthPoint + vec2(20.);
    vec2 min = depthPoint - vec2(20.);

	
	if( st.s >= min.x && st.s <= max.x && st.t >= min.y && st.t <= max.y){

    vec2 divisor = sampleDivisor * 10.;
//    float divisor1 = sampleDivisor.y * 1.5;

        samplePos = st.st - mod( st.st, divisor );
        
    }else{
       samplePos = st.st - mod( st.st,  sampleDivisor);

    }
    
    gl_FragColor = texture2DRect( src_tex_unit0, samplePos );

//	samplePos = gl_TexCoord[0].st - mod( gl_TexCoord[0].st, sampleDivisor );
//    * (vec4(1.0, 0.0, 0.0, 1.0) * sampleDivisor.x)
//    vec2(10.
}